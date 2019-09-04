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
struct TYPE_4__ {int reqbufs_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_dev; } ;
struct fimc_dev {int /*<<< orphan*/  slock; TYPE_2__ vid_cap; int /*<<< orphan*/  state; int /*<<< orphan*/  irq_queue; TYPE_1__ m2m; } ;
struct fimc_ctx {int state; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FIMC_CTX_SHUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ST_CAPT_JPEG ; 
 int /*<<< orphan*/  ST_CAPT_PEND ; 
 int /*<<< orphan*/  ST_M2M_PEND ; 
 int /*<<< orphan*/  ST_M2M_SUSPENDED ; 
 int /*<<< orphan*/  ST_M2M_SUSPENDING ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  fimc_capture_irq_handler (struct fimc_dev*,int) ; 
 int /*<<< orphan*/  fimc_hw_clear_irq (struct fimc_dev*) ; 
 int /*<<< orphan*/  fimc_m2m_job_finish (struct fimc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fimc_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fimc_irq_handler(int irq, void *priv)
{
	struct fimc_dev *fimc = priv;
	struct fimc_ctx *ctx;

	fimc_hw_clear_irq(fimc);

	spin_lock(&fimc->slock);

	if (test_and_clear_bit(ST_M2M_PEND, &fimc->state)) {
		if (test_and_clear_bit(ST_M2M_SUSPENDING, &fimc->state)) {
			set_bit(ST_M2M_SUSPENDED, &fimc->state);
			wake_up(&fimc->irq_queue);
			goto out;
		}
		ctx = v4l2_m2m_get_curr_priv(fimc->m2m.m2m_dev);
		if (ctx != NULL) {
			spin_unlock(&fimc->slock);
			fimc_m2m_job_finish(ctx, VB2_BUF_STATE_DONE);

			if (ctx->state & FIMC_CTX_SHUT) {
				ctx->state &= ~FIMC_CTX_SHUT;
				wake_up(&fimc->irq_queue);
			}
			return IRQ_HANDLED;
		}
	} else if (test_bit(ST_CAPT_PEND, &fimc->state)) {
		int last_buf = test_bit(ST_CAPT_JPEG, &fimc->state) &&
				fimc->vid_cap.reqbufs_count == 1;
		fimc_capture_irq_handler(fimc, !last_buf);
	}
out:
	spin_unlock(&fimc->slock);
	return IRQ_HANDLED;
}