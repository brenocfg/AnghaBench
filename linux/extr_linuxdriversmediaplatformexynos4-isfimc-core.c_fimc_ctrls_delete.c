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
struct fimc_ctrls {int ready; int /*<<< orphan*/ * alpha; int /*<<< orphan*/  handler; } ;
struct fimc_ctx {struct fimc_ctrls ctrls; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

void fimc_ctrls_delete(struct fimc_ctx *ctx)
{
	struct fimc_ctrls *ctrls = &ctx->ctrls;

	if (ctrls->ready) {
		v4l2_ctrl_handler_free(&ctrls->handler);
		ctrls->ready = false;
		ctrls->alpha = NULL;
	}
}