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
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct fimc_ctx *ctx = q->drv_priv;
	int ret;

	ret = pm_runtime_get_sync(&ctx->fimc_dev->pdev->dev);
	return ret > 0 ? 0 : ret;
}