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
struct TYPE_2__ {struct bdisp_ctx* ctx; } ;
struct bdisp_dev {int /*<<< orphan*/  state; int /*<<< orphan*/  slock; TYPE_1__ m2m; } ;
struct bdisp_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_M2M_SUSPENDED ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  bdisp_job_finish (struct bdisp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bdisp_m2m_resume(struct bdisp_dev *bdisp)
{
	struct bdisp_ctx *ctx;
	unsigned long flags;

	spin_lock_irqsave(&bdisp->slock, flags);
	ctx = bdisp->m2m.ctx;
	bdisp->m2m.ctx = NULL;
	spin_unlock_irqrestore(&bdisp->slock, flags);

	if (test_and_clear_bit(ST_M2M_SUSPENDED, &bdisp->state))
		bdisp_job_finish(ctx, VB2_BUF_STATE_ERROR);

	return 0;
}