#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ivtv_stream {scalar_t__ type; scalar_t__ sg_processed; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct ivtv {size_t cur_dma_stream; int dma_retries; int /*<<< orphan*/  dma_waitq; int /*<<< orphan*/  i_flags; TYPE_1__ dma_timer; struct ivtv_stream* streams; int /*<<< orphan*/  enc_mbox; } ;

/* Variables and functions */
 int CX2341X_MBOX_MAX_DATA ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*,int,int,int,size_t) ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_MPG ; 
 int /*<<< orphan*/  IVTV_F_I_DMA ; 
 int /*<<< orphan*/  IVTV_F_I_UDMA ; 
 size_t IVTV_MAX_STREAMS ; 
 int /*<<< orphan*/  IVTV_MBOX_DMA_END ; 
 int /*<<< orphan*/  IVTV_REG_DMASTATUS ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ivtv_api_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ivtv_dma_dec_start (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_dma_enc_start_xfer (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_udma_start (struct ivtv*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ivtv_irq_dma_err(struct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	u32 status;

	del_timer(&itv->dma_timer);

	ivtv_api_get_data(&itv->enc_mbox, IVTV_MBOX_DMA_END, 2, data);
	status = read_reg(IVTV_REG_DMASTATUS);
	IVTV_DEBUG_WARN("DMA ERROR %08x %08x %08x %d\n", data[0], data[1],
				status, itv->cur_dma_stream);
	/*
	 * We do *not* write back to the IVTV_REG_DMASTATUS register to
	 * clear the error status, if either the encoder write (0x02) or
	 * decoder read (0x01) bus master DMA operation do not indicate
	 * completed.  We can race with the DMA engine, which may have
	 * transitioned to completed status *after* we read the register.
	 * Setting a IVTV_REG_DMASTATUS flag back to "busy" status, after the
	 * DMA engine has completed, will cause the DMA engine to stop working.
	 */
	status &= 0x3;
	if (status == 0x3)
		write_reg(status, IVTV_REG_DMASTATUS);

	if (!test_bit(IVTV_F_I_UDMA, &itv->i_flags) &&
	    itv->cur_dma_stream >= 0 && itv->cur_dma_stream < IVTV_MAX_STREAMS) {
		struct ivtv_stream *s = &itv->streams[itv->cur_dma_stream];

		if (s->type >= IVTV_DEC_STREAM_TYPE_MPG) {
			/* retry */
			/*
			 * FIXME - handle cases of DMA error similar to
			 * encoder below, except conditioned on status & 0x1
			 */
			ivtv_dma_dec_start(s);
			return;
		} else {
			if ((status & 0x2) == 0) {
				/*
				 * CX2341x Bus Master DMA write is ongoing.
				 * Reset the timer and let it complete.
				 */
				itv->dma_timer.expires =
						jiffies + msecs_to_jiffies(600);
				add_timer(&itv->dma_timer);
				return;
			}

			if (itv->dma_retries < 3) {
				/*
				 * CX2341x Bus Master DMA write has ended.
				 * Retry the write, starting with the first
				 * xfer segment. Just retrying the current
				 * segment is not sufficient.
				 */
				s->sg_processed = 0;
				itv->dma_retries++;
				ivtv_dma_enc_start_xfer(s);
				return;
			}
			/* Too many retries, give up on this one */
		}

	}
	if (test_bit(IVTV_F_I_UDMA, &itv->i_flags)) {
		ivtv_udma_start(itv);
		return;
	}
	clear_bit(IVTV_F_I_UDMA, &itv->i_flags);
	clear_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = -1;
	wake_up(&itv->dma_waitq);
}