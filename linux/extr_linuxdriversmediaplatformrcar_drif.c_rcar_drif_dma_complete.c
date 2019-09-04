#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct rcar_drif_sdr {size_t produced; int num_cur_ch; unsigned int hwbuf_size; TYPE_1__* fmt; int /*<<< orphan*/  dma_lock; int /*<<< orphan*/  vb_queue; } ;
struct rcar_drif_hwbuf {int status; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_7__ {size_t sequence; TYPE_3__ vb2_buf; int /*<<< orphan*/  field; } ;
struct rcar_drif_frame_buf {TYPE_2__ vb; } ;
struct rcar_drif {scalar_t__ num; struct rcar_drif_hwbuf* buf; struct rcar_drif_sdr* sdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  buffersize; } ;

/* Variables and functions */
 int RCAR_DRIF_BUF_DONE ; 
 int RCAR_DRIF_BUF_OVERFLOW ; 
 int RCAR_DRIF_MAX_CHANNEL ; 
 size_t RCAR_DRIF_NUM_HWBUFS ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rcar_drif_bufs_clear (struct rcar_drif_hwbuf**,int) ; 
 int /*<<< orphan*/  rcar_drif_bufs_done (struct rcar_drif_hwbuf**) ; 
 scalar_t__ rcar_drif_bufs_overflow (struct rcar_drif_hwbuf**) ; 
 int /*<<< orphan*/  rcar_drif_channel_complete (struct rcar_drif*,size_t) ; 
 struct rcar_drif_frame_buf* rcar_drif_get_fbuf (struct rcar_drif_sdr*) ; 
 int /*<<< orphan*/  rdrif_dbg (struct rcar_drif_sdr*,char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct rcar_drif_hwbuf* to_rcar_drif_buf_pair (struct rcar_drif_sdr*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_is_streaming (int /*<<< orphan*/ *) ; 
 scalar_t__ vb2_plane_vaddr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_drif_dma_complete(void *dma_async_param)
{
	struct rcar_drif *ch = dma_async_param;
	struct rcar_drif_sdr *sdr = ch->sdr;
	struct rcar_drif_hwbuf *buf[RCAR_DRIF_MAX_CHANNEL];
	struct rcar_drif_frame_buf *fbuf;
	bool overflow = false;
	u32 idx, produced;
	unsigned int i;

	spin_lock(&sdr->dma_lock);

	/* DMA can be terminated while the callback was waiting on lock */
	if (!vb2_is_streaming(&sdr->vb_queue)) {
		spin_unlock(&sdr->dma_lock);
		return;
	}

	idx = sdr->produced % RCAR_DRIF_NUM_HWBUFS;
	rcar_drif_channel_complete(ch, idx);

	if (sdr->num_cur_ch == RCAR_DRIF_MAX_CHANNEL) {
		buf[0] = ch->num ? to_rcar_drif_buf_pair(sdr, ch->num, idx) :
				&ch->buf[idx];
		buf[1] = ch->num ? &ch->buf[idx] :
				to_rcar_drif_buf_pair(sdr, ch->num, idx);

		/* Check if both DMA buffers are done */
		if (!rcar_drif_bufs_done(buf)) {
			spin_unlock(&sdr->dma_lock);
			return;
		}

		/* Clear buf done status */
		rcar_drif_bufs_clear(buf, RCAR_DRIF_BUF_DONE);

		if (rcar_drif_bufs_overflow(buf)) {
			overflow = true;
			/* Clear the flag in status */
			rcar_drif_bufs_clear(buf, RCAR_DRIF_BUF_OVERFLOW);
		}
	} else {
		buf[0] = &ch->buf[idx];
		if (buf[0]->status & RCAR_DRIF_BUF_OVERFLOW) {
			overflow = true;
			/* Clear the flag in status */
			buf[0]->status &= ~RCAR_DRIF_BUF_OVERFLOW;
		}
	}

	/* Buffer produced for consumption */
	produced = sdr->produced++;
	spin_unlock(&sdr->dma_lock);

	rdrif_dbg(sdr, "ch%u: prod %u\n", ch->num, produced);

	/* Get fbuf */
	fbuf = rcar_drif_get_fbuf(sdr);
	if (!fbuf)
		return;

	for (i = 0; i < RCAR_DRIF_MAX_CHANNEL; i++)
		memcpy(vb2_plane_vaddr(&fbuf->vb.vb2_buf, 0) +
		       i * sdr->hwbuf_size, buf[i]->addr, sdr->hwbuf_size);

	fbuf->vb.field = V4L2_FIELD_NONE;
	fbuf->vb.sequence = produced;
	fbuf->vb.vb2_buf.timestamp = ktime_get_ns();
	vb2_set_plane_payload(&fbuf->vb.vb2_buf, 0, sdr->fmt->buffersize);

	/* Set error state on overflow */
	vb2_buffer_done(&fbuf->vb.vb2_buf,
			overflow ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
}