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
typedef  scalar_t__ u32 ;
struct cal_dmaqueue {int /*<<< orphan*/  active; } ;
struct cal_dev {struct cal_ctx** ctx; } ;
struct cal_ctx {scalar_t__ cur_frm; scalar_t__ next_frm; int /*<<< orphan*/  slock; struct cal_dmaqueue vidq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_HL_IRQSTATUS (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cal_process_buffer_complete (struct cal_ctx*) ; 
 int /*<<< orphan*/  cal_schedule_next_buffer (struct cal_ctx*) ; 
 scalar_t__ isportirqset (scalar_t__,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ reg_read (struct cal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct cal_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cal_irq(int irq_cal, void *data)
{
	struct cal_dev *dev = (struct cal_dev *)data;
	struct cal_ctx *ctx;
	struct cal_dmaqueue *dma_q;
	u32 irqst2, irqst3;

	/* Check which DMA just finished */
	irqst2 = reg_read(dev, CAL_HL_IRQSTATUS(2));
	if (irqst2) {
		/* Clear Interrupt status */
		reg_write(dev, CAL_HL_IRQSTATUS(2), irqst2);

		/* Need to check both port */
		if (isportirqset(irqst2, 1)) {
			ctx = dev->ctx[0];

			if (ctx->cur_frm != ctx->next_frm)
				cal_process_buffer_complete(ctx);
		}

		if (isportirqset(irqst2, 2)) {
			ctx = dev->ctx[1];

			if (ctx->cur_frm != ctx->next_frm)
				cal_process_buffer_complete(ctx);
		}
	}

	/* Check which DMA just started */
	irqst3 = reg_read(dev, CAL_HL_IRQSTATUS(3));
	if (irqst3) {
		/* Clear Interrupt status */
		reg_write(dev, CAL_HL_IRQSTATUS(3), irqst3);

		/* Need to check both port */
		if (isportirqset(irqst3, 1)) {
			ctx = dev->ctx[0];
			dma_q = &ctx->vidq;

			spin_lock(&ctx->slock);
			if (!list_empty(&dma_q->active) &&
			    ctx->cur_frm == ctx->next_frm)
				cal_schedule_next_buffer(ctx);
			spin_unlock(&ctx->slock);
		}

		if (isportirqset(irqst3, 2)) {
			ctx = dev->ctx[1];
			dma_q = &ctx->vidq;

			spin_lock(&ctx->slock);
			if (!list_empty(&dma_q->active) &&
			    ctx->cur_frm == ctx->next_frm)
				cal_schedule_next_buffer(ctx);
			spin_unlock(&ctx->slock);
		}
	}

	return IRQ_HANDLED;
}