#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * v4l2_dev; } ;
struct ivtv_stream {int /*<<< orphan*/  s_flags; int /*<<< orphan*/  name; TYPE_1__ vdev; struct ivtv* itv; } ;
struct TYPE_6__ {TYPE_2__* mbox; } ;
struct ivtv {int /*<<< orphan*/  decoding; int /*<<< orphan*/  irqmask; TYPE_3__ dec_mbox; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_SET_DMA_BLOCK_SIZE ; 
 int /*<<< orphan*/  CX2341X_DEC_SET_EVENT_NOTIFICATION ; 
 int /*<<< orphan*/  CX2341X_DEC_START_PLAYBACK ; 
 int EINVAL ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IVTV_DEBUG_IRQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMING ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMOFF ; 
 int /*<<< orphan*/  IVTV_IRQ_DEC_AUD_MODE_CHG ; 
 int /*<<< orphan*/  IVTV_IRQ_MASK_DECODE ; 
 size_t IVTV_MBOX_DMA ; 
 size_t IVTV_MBOX_DMA_END ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_clear_irq_mask (struct ivtv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_msleep_timeout (int,int /*<<< orphan*/ ) ; 
 int ivtv_setup_v4l2_decode_stream (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int,...) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ivtv_start_v4l2_decode_stream(struct ivtv_stream *s, int gop_offset)
{
	struct ivtv *itv = s->itv;
	int rc;

	if (s->vdev.v4l2_dev == NULL)
		return -EINVAL;

	if (test_and_set_bit(IVTV_F_S_STREAMING, &s->s_flags))
		return 0;	/* already started */

	IVTV_DEBUG_INFO("Starting decode stream %s (gop_offset %d)\n", s->name, gop_offset);

	rc = ivtv_setup_v4l2_decode_stream(s);
	if (rc < 0) {
		clear_bit(IVTV_F_S_STREAMING, &s->s_flags);
		return rc;
	}

	/* set dma size to 65536 bytes */
	ivtv_vapi(itv, CX2341X_DEC_SET_DMA_BLOCK_SIZE, 1, 65536);

	/* Clear Streamoff */
	clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);

	/* Zero out decoder counters */
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[0]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[1]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[2]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[3]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[0]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[1]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[2]);
	writel(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[3]);

	/* turn on notification of dual/stereo mode change */
	ivtv_vapi(itv, CX2341X_DEC_SET_EVENT_NOTIFICATION, 4, 0, 1, IVTV_IRQ_DEC_AUD_MODE_CHG, -1);

	/* start playback */
	ivtv_vapi(itv, CX2341X_DEC_START_PLAYBACK, 2, gop_offset, 0);

	/* Let things settle before we actually start */
	ivtv_msleep_timeout(10, 0);

	/* Clear the following Interrupt mask bits for decoding */
	ivtv_clear_irq_mask(itv, IVTV_IRQ_MASK_DECODE);
	IVTV_DEBUG_IRQ("IRQ Mask is now: 0x%08x\n", itv->irqmask);

	/* you're live! sit back and await interrupts :) */
	atomic_inc(&itv->decoding);
	return 0;
}