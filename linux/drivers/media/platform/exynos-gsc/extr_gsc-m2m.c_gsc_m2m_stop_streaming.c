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
struct vb2_queue {struct gsc_ctx* drv_priv; } ;
struct gsc_ctx {TYPE_2__* gsc_dev; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gsc_m2m_cleanup_queue (struct gsc_ctx*) ; 
 int /*<<< orphan*/  __gsc_m2m_job_abort (struct gsc_ctx*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gsc_m2m_stop_streaming(struct vb2_queue *q)
{
	struct gsc_ctx *ctx = q->drv_priv;

	__gsc_m2m_job_abort(ctx);

	__gsc_m2m_cleanup_queue(ctx);

	pm_runtime_put(&ctx->gsc_dev->pdev->dev);
}