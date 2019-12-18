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
struct TYPE_2__ {int /*<<< orphan*/  m2m_dev; } ;
struct gsc_dev {int /*<<< orphan*/  slock; int /*<<< orphan*/  irq_queue; TYPE_1__ m2m; int /*<<< orphan*/  state; } ;
struct gsc_ctx {int state; int /*<<< orphan*/  m2m_ctx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int GSC_CTX_STOP_REQ ; 
 int GSC_IRQ_OVERRUN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ST_M2M_PEND ; 
 int /*<<< orphan*/  ST_M2M_SUSPENDED ; 
 int /*<<< orphan*/  ST_M2M_SUSPENDING ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  gsc_hw_clear_irq (struct gsc_dev*,int) ; 
 int /*<<< orphan*/  gsc_hw_enable_control (struct gsc_dev*,int) ; 
 int gsc_hw_get_irq_status (struct gsc_dev*) ; 
 int /*<<< orphan*/  gsc_m2m_job_finish (struct gsc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct gsc_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t gsc_irq_handler(int irq, void *priv)
{
	struct gsc_dev *gsc = priv;
	struct gsc_ctx *ctx;
	int gsc_irq;

	gsc_irq = gsc_hw_get_irq_status(gsc);
	gsc_hw_clear_irq(gsc, gsc_irq);

	if (gsc_irq == GSC_IRQ_OVERRUN) {
		pr_err("Local path input over-run interrupt has occurred!\n");
		return IRQ_HANDLED;
	}

	spin_lock(&gsc->slock);

	if (test_and_clear_bit(ST_M2M_PEND, &gsc->state)) {

		gsc_hw_enable_control(gsc, false);

		if (test_and_clear_bit(ST_M2M_SUSPENDING, &gsc->state)) {
			set_bit(ST_M2M_SUSPENDED, &gsc->state);
			wake_up(&gsc->irq_queue);
			goto isr_unlock;
		}
		ctx = v4l2_m2m_get_curr_priv(gsc->m2m.m2m_dev);

		if (!ctx || !ctx->m2m_ctx)
			goto isr_unlock;

		spin_unlock(&gsc->slock);
		gsc_m2m_job_finish(ctx, VB2_BUF_STATE_DONE);

		/* wake_up job_abort, stop_streaming */
		if (ctx->state & GSC_CTX_STOP_REQ) {
			ctx->state &= ~GSC_CTX_STOP_REQ;
			wake_up(&gsc->irq_queue);
		}
		return IRQ_HANDLED;
	}

isr_unlock:
	spin_unlock(&gsc->slock);
	return IRQ_HANDLED;
}