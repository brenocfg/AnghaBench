#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buffers; } ;
struct ivtv_stream {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  waitq; TYPE_2__ q_full; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  dma_pts; TYPE_2__ q_io; int /*<<< orphan*/  q_free; struct ivtv* itv; } ;
struct ivtv_buffer {scalar_t__ readpos; scalar_t__ bytesused; int b_flags; } ;
struct TYPE_3__ {struct ivtv_buffer sliced_mpeg_buf; } ;
struct ivtv {int /*<<< orphan*/  serialize_lock; TYPE_1__ vbi; scalar_t__ dualwatch_jiffies; struct ivtv_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_VBI ; 
 scalar_t__ IVTV_ENC_STREAM_TYPE_MPG ; 
 size_t IVTV_ENC_STREAM_TYPE_VBI ; 
 int IVTV_F_B_NEED_BUF_SWAP ; 
 int /*<<< orphan*/  IVTV_F_S_APPL_IO ; 
 int /*<<< orphan*/  IVTV_F_S_INTERNAL_USE ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_buf_swap (struct ivtv_buffer*) ; 
 struct ivtv_buffer* ivtv_dequeue (struct ivtv_stream*,TYPE_2__*) ; 
 int /*<<< orphan*/  ivtv_dualwatch (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_enqueue (struct ivtv_stream*,struct ivtv_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_process_vbi_data (struct ivtv*,struct ivtv_buffer*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ivtv_update_pgm_info (struct ivtv*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static struct ivtv_buffer *ivtv_get_buffer(struct ivtv_stream *s, int non_block, int *err)
{
	struct ivtv *itv = s->itv;
	struct ivtv_stream *s_vbi = &itv->streams[IVTV_ENC_STREAM_TYPE_VBI];
	struct ivtv_buffer *buf;
	DEFINE_WAIT(wait);

	*err = 0;
	while (1) {
		if (s->type == IVTV_ENC_STREAM_TYPE_MPG) {
			/* Process pending program info updates and pending VBI data */
			ivtv_update_pgm_info(itv);

			if (time_after(jiffies,
				       itv->dualwatch_jiffies +
				       msecs_to_jiffies(1000))) {
				itv->dualwatch_jiffies = jiffies;
				ivtv_dualwatch(itv);
			}

			if (test_bit(IVTV_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
			    !test_bit(IVTV_F_S_APPL_IO, &s_vbi->s_flags)) {
				while ((buf = ivtv_dequeue(s_vbi, &s_vbi->q_full))) {
					/* byteswap and process VBI data */
					ivtv_process_vbi_data(itv, buf, s_vbi->dma_pts, s_vbi->type);
					ivtv_enqueue(s_vbi, buf, &s_vbi->q_free);
				}
			}
			buf = &itv->vbi.sliced_mpeg_buf;
			if (buf->readpos != buf->bytesused) {
				return buf;
			}
		}

		/* do we have leftover data? */
		buf = ivtv_dequeue(s, &s->q_io);
		if (buf)
			return buf;

		/* do we have new data? */
		buf = ivtv_dequeue(s, &s->q_full);
		if (buf) {
			if ((buf->b_flags & IVTV_F_B_NEED_BUF_SWAP) == 0)
				return buf;
			buf->b_flags &= ~IVTV_F_B_NEED_BUF_SWAP;
			if (s->type == IVTV_ENC_STREAM_TYPE_MPG)
				/* byteswap MPG data */
				ivtv_buf_swap(buf);
			else if (s->type != IVTV_DEC_STREAM_TYPE_VBI) {
				/* byteswap and process VBI data */
				ivtv_process_vbi_data(itv, buf, s->dma_pts, s->type);
			}
			return buf;
		}

		/* return if end of stream */
		if (s->type != IVTV_DEC_STREAM_TYPE_VBI && !test_bit(IVTV_F_S_STREAMING, &s->s_flags)) {
			IVTV_DEBUG_INFO("EOS %s\n", s->name);
			return NULL;
		}

		/* return if file was opened with O_NONBLOCK */
		if (non_block) {
			*err = -EAGAIN;
			return NULL;
		}

		/* wait for more data to arrive */
		mutex_unlock(&itv->serialize_lock);
		prepare_to_wait(&s->waitq, &wait, TASK_INTERRUPTIBLE);
		/* New buffers might have become available before we were added to the waitqueue */
		if (!s->q_full.buffers)
			schedule();
		finish_wait(&s->waitq, &wait);
		mutex_lock(&itv->serialize_lock);
		if (signal_pending(current)) {
			/* return if a signal was received */
			IVTV_DEBUG_INFO("User stopped %s\n", s->name);
			*err = -EINTR;
			return NULL;
		}
	}
}