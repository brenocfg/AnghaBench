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
struct vb2_queue {struct fimc_ctx* drv_priv; } ;
struct fimc_ctx {TYPE_2__* fimc_dev; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  fimc_m2m_job_finish (struct fimc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_m2m_shutdown (struct fimc_ctx*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_streaming(struct vb2_queue *q)
{
	struct fimc_ctx *ctx = q->drv_priv;


	fimc_m2m_shutdown(ctx);
	fimc_m2m_job_finish(ctx, VB2_BUF_STATE_ERROR);
	pm_runtime_put(&ctx->fimc_dev->pdev->dev);
}