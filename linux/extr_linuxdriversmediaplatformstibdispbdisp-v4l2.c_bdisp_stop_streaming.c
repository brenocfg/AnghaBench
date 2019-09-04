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
struct vb2_queue {struct bdisp_ctx* drv_priv; } ;
struct bdisp_ctx {TYPE_1__* bdisp_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bdisp_job_abort (struct bdisp_ctx*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bdisp_stop_streaming(struct vb2_queue *q)
{
	struct bdisp_ctx *ctx = q->drv_priv;

	__bdisp_job_abort(ctx);

	pm_runtime_put(ctx->bdisp_dev->dev);
}