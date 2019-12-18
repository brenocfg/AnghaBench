#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bytesused; } ;
struct ivtv_stream {scalar_t__ sg_processed; scalar_t__ sg_processing_size; scalar_t__ type; int /*<<< orphan*/  waitq; int /*<<< orphan*/  q_free; TYPE_1__ q_dma; int /*<<< orphan*/  name; } ;
struct ivtv_buffer {int dummy; } ;
struct ivtv {size_t cur_dma_stream; int dma_retries; int /*<<< orphan*/  dma_waitq; int /*<<< orphan*/  i_flags; struct ivtv_stream* streams; int /*<<< orphan*/  dma_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_SCHED_DMA_FROM_HOST ; 
 int /*<<< orphan*/  IVTV_DEBUG_HI_DMA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IVTV_DEBUG_HI_IRQ (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*,int,scalar_t__,scalar_t__,int) ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  IVTV_F_I_DMA ; 
 int /*<<< orphan*/  IVTV_F_I_UDMA ; 
 int /*<<< orphan*/  IVTV_REG_DMASTATUS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_buf_sync_for_cpu (struct ivtv_stream*,struct ivtv_buffer*) ; 
 struct ivtv_buffer* ivtv_dequeue (struct ivtv_stream*,TYPE_1__*) ; 
 int /*<<< orphan*/  ivtv_dma_dec_start_xfer (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_enqueue (struct ivtv_stream*,struct ivtv_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_stream_sync_for_cpu (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ivtv_irq_dma_read(struct ivtv *itv)
{
	struct ivtv_stream *s = NULL;
	struct ivtv_buffer *buf;
	int hw_stream_type = 0;

	IVTV_DEBUG_HI_IRQ("DEC DMA READ\n");

	del_timer(&itv->dma_timer);

	if (!test_bit(IVTV_F_I_UDMA, &itv->i_flags) && itv->cur_dma_stream < 0)
		return;

	if (!test_bit(IVTV_F_I_UDMA, &itv->i_flags)) {
		s = &itv->streams[itv->cur_dma_stream];
		ivtv_stream_sync_for_cpu(s);

		if (read_reg(IVTV_REG_DMASTATUS) & 0x14) {
			IVTV_DEBUG_WARN("DEC DMA ERROR %x (xfer %d of %d, retry %d)\n",
					read_reg(IVTV_REG_DMASTATUS),
					s->sg_processed, s->sg_processing_size, itv->dma_retries);
			write_reg(read_reg(IVTV_REG_DMASTATUS) & 3, IVTV_REG_DMASTATUS);
			if (itv->dma_retries == 3) {
				/* Too many retries, give up on this frame */
				itv->dma_retries = 0;
				s->sg_processed = s->sg_processing_size;
			}
			else {
				/* Retry, starting with the first xfer segment.
				   Just retrying the current segment is not sufficient. */
				s->sg_processed = 0;
				itv->dma_retries++;
			}
		}
		if (s->sg_processed < s->sg_processing_size) {
			/* DMA next buffer */
			ivtv_dma_dec_start_xfer(s);
			return;
		}
		if (s->type == IVTV_DEC_STREAM_TYPE_YUV)
			hw_stream_type = 2;
		IVTV_DEBUG_HI_DMA("DEC DATA READ %s: %d\n", s->name, s->q_dma.bytesused);

		/* For some reason must kick the firmware, like PIO mode,
		   I think this tells the firmware we are done and the size
		   of the xfer so it can calculate what we need next.
		   I think we can do this part ourselves but would have to
		   fully calculate xfer info ourselves and not use interrupts
		 */
		ivtv_vapi(itv, CX2341X_DEC_SCHED_DMA_FROM_HOST, 3, 0, s->q_dma.bytesused,
				hw_stream_type);

		/* Free last DMA call */
		while ((buf = ivtv_dequeue(s, &s->q_dma)) != NULL) {
			ivtv_buf_sync_for_cpu(s, buf);
			ivtv_enqueue(s, buf, &s->q_free);
		}
		wake_up(&s->waitq);
	}
	clear_bit(IVTV_F_I_UDMA, &itv->i_flags);
	clear_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = -1;
	wake_up(&itv->dma_waitq);
}