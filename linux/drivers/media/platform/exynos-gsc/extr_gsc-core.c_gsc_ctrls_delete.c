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
struct gsc_ctx {int ctrls_rdy; int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

void gsc_ctrls_delete(struct gsc_ctx *ctx)
{
	if (ctx->ctrls_rdy) {
		v4l2_ctrl_handler_free(&ctx->ctrl_handler);
		ctx->ctrls_rdy = false;
	}
}