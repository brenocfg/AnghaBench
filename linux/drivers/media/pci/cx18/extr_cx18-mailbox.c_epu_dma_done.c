#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct cx18_stream {int mdl_base_idx; int buffers; scalar_t__ type; int id; int /*<<< orphan*/  waitq; int /*<<< orphan*/  q_full; int /*<<< orphan*/  q_free; int /*<<< orphan*/  name; } ;
struct cx18_mdl_ack {int id; int /*<<< orphan*/  data_used; } ;
struct cx18_mdl {int bytesused; } ;
struct cx18_mailbox {int* args; int /*<<< orphan*/  request; } ;
struct cx18_in_work_order {int flags; struct cx18_mdl_ack* mdl_ack; struct cx18_mailbox mb; } ;
struct cx18 {int /*<<< orphan*/  dma_waitq; int /*<<< orphan*/ * pcm_announce_callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_HI_DMA (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_IDX ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_PCM ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_TS ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_YUV ; 
 int CX18_F_EWO_MB_STALE_UPON_RECEIPT ; 
 int /*<<< orphan*/  CX18_WARN (char*,int,...) ; 
 int /*<<< orphan*/  cx18_enqueue (struct cx18_stream*,struct cx18_mdl*,int /*<<< orphan*/ *) ; 
 struct cx18_stream* cx18_handle_to_stream (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_mdl_send_to_alsa (struct cx18*,struct cx18_stream*,struct cx18_mdl*) ; 
 int /*<<< orphan*/  cx18_mdl_send_to_dvb (struct cx18_stream*,struct cx18_mdl*) ; 
 int /*<<< orphan*/  cx18_mdl_send_to_videobuf (struct cx18_stream*,struct cx18_mdl*) ; 
 struct cx18_mdl* cx18_queue_get_mdl (struct cx18_stream*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_stream_load_fw_queue (struct cx18_stream*) ; 
 int /*<<< orphan*/  cx18_stream_rotate_idx_mdls (struct cx18*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void epu_dma_done(struct cx18 *cx, struct cx18_in_work_order *order)
{
	u32 handle, mdl_ack_count, id;
	struct cx18_mailbox *mb;
	struct cx18_mdl_ack *mdl_ack;
	struct cx18_stream *s;
	struct cx18_mdl *mdl;
	int i;

	mb = &order->mb;
	handle = mb->args[0];
	s = cx18_handle_to_stream(cx, handle);

	if (s == NULL) {
		CX18_WARN("Got DMA done notification for unknown/inactive handle %d, %s mailbox seq no %d\n",
			  handle,
			  (order->flags & CX18_F_EWO_MB_STALE_UPON_RECEIPT) ?
			  "stale" : "good", mb->request);
		return;
	}

	mdl_ack_count = mb->args[2];
	mdl_ack = order->mdl_ack;
	for (i = 0; i < mdl_ack_count; i++, mdl_ack++) {
		id = mdl_ack->id;
		/*
		 * Simple integrity check for processing a stale (and possibly
		 * inconsistent mailbox): make sure the MDL id is in the
		 * valid range for the stream.
		 *
		 * We go through the trouble of dealing with stale mailboxes
		 * because most of the time, the mailbox data is still valid and
		 * unchanged (and in practice the firmware ping-pongs the
		 * two mdl_ack buffers so mdl_acks are not stale).
		 *
		 * There are occasions when we get a half changed mailbox,
		 * which this check catches for a handle & id mismatch.  If the
		 * handle and id do correspond, the worst case is that we
		 * completely lost the old MDL, but pick up the new MDL
		 * early (but the new mdl_ack is guaranteed to be good in this
		 * case as the firmware wouldn't point us to a new mdl_ack until
		 * it's filled in).
		 *
		 * cx18_queue_get_mdl() will detect the lost MDLs
		 * and send them back to q_free for fw rotation eventually.
		 */
		if ((order->flags & CX18_F_EWO_MB_STALE_UPON_RECEIPT) &&
		    !(id >= s->mdl_base_idx &&
		      id < (s->mdl_base_idx + s->buffers))) {
			CX18_WARN("Fell behind! Ignoring stale mailbox with  inconsistent data. Lost MDL for mailbox seq no %d\n",
				  mb->request);
			break;
		}
		mdl = cx18_queue_get_mdl(s, id, mdl_ack->data_used);

		CX18_DEBUG_HI_DMA("DMA DONE for %s (MDL %d)\n", s->name, id);
		if (mdl == NULL) {
			CX18_WARN("Could not find MDL %d for stream %s\n",
				  id, s->name);
			continue;
		}

		CX18_DEBUG_HI_DMA("%s recv bytesused = %d\n",
				  s->name, mdl->bytesused);

		if (s->type == CX18_ENC_STREAM_TYPE_TS) {
			cx18_mdl_send_to_dvb(s, mdl);
			cx18_enqueue(s, mdl, &s->q_free);
		} else if (s->type == CX18_ENC_STREAM_TYPE_PCM) {
			/* Pass the data to cx18-alsa */
			if (cx->pcm_announce_callback != NULL) {
				cx18_mdl_send_to_alsa(cx, s, mdl);
				cx18_enqueue(s, mdl, &s->q_free);
			} else {
				cx18_enqueue(s, mdl, &s->q_full);
			}
		} else if (s->type == CX18_ENC_STREAM_TYPE_YUV) {
			cx18_mdl_send_to_videobuf(s, mdl);
			cx18_enqueue(s, mdl, &s->q_free);
		} else {
			cx18_enqueue(s, mdl, &s->q_full);
			if (s->type == CX18_ENC_STREAM_TYPE_IDX)
				cx18_stream_rotate_idx_mdls(cx);
		}
	}
	/* Put as many MDLs as possible back into fw use */
	cx18_stream_load_fw_queue(s);

	wake_up(&cx->dma_waitq);
	if (s->id != -1)
		wake_up(&s->waitq);
}