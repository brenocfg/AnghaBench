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
struct TYPE_3__ {int /*<<< orphan*/  m2m_dev; } ;
struct bdisp_dev {int /*<<< orphan*/  slock; int /*<<< orphan*/  irq_queue; TYPE_1__ m2m; int /*<<< orphan*/  state; int /*<<< orphan*/  timeout_work; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct bdisp_ctx {TYPE_2__ fh; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BDISP_CTX_STOP_REQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ST_M2M_RUNNING ; 
 int /*<<< orphan*/  ST_M2M_SUSPENDED ; 
 int /*<<< orphan*/  ST_M2M_SUSPENDING ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 scalar_t__ bdisp_ctx_state_is_set (int /*<<< orphan*/ ,struct bdisp_ctx*) ; 
 int /*<<< orphan*/  bdisp_ctx_state_lock_clear (int /*<<< orphan*/ ,struct bdisp_ctx*) ; 
 int /*<<< orphan*/  bdisp_dbg_perf_end (struct bdisp_dev*) ; 
 int /*<<< orphan*/  bdisp_job_finish (struct bdisp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bdisp_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bdisp_irq_thread(int irq, void *priv)
{
	struct bdisp_dev *bdisp = priv;
	struct bdisp_ctx *ctx;

	spin_lock(&bdisp->slock);

	bdisp_dbg_perf_end(bdisp);

	cancel_delayed_work(&bdisp->timeout_work);

	if (!test_and_clear_bit(ST_M2M_RUNNING, &bdisp->state))
		goto isr_unlock;

	if (test_and_clear_bit(ST_M2M_SUSPENDING, &bdisp->state)) {
		set_bit(ST_M2M_SUSPENDED, &bdisp->state);
		wake_up(&bdisp->irq_queue);
		goto isr_unlock;
	}

	ctx = v4l2_m2m_get_curr_priv(bdisp->m2m.m2m_dev);
	if (!ctx || !ctx->fh.m2m_ctx)
		goto isr_unlock;

	spin_unlock(&bdisp->slock);

	bdisp_job_finish(ctx, VB2_BUF_STATE_DONE);

	if (bdisp_ctx_state_is_set(BDISP_CTX_STOP_REQ, ctx)) {
		bdisp_ctx_state_lock_clear(BDISP_CTX_STOP_REQ, ctx);
		wake_up(&bdisp->irq_queue);
	}

	return IRQ_HANDLED;

isr_unlock:
	spin_unlock(&bdisp->slock);

	return IRQ_HANDLED;
}