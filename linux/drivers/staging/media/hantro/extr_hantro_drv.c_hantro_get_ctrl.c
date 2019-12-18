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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {void* p; } ;
struct v4l2_ctrl {TYPE_1__ p_cur; } ;
struct hantro_ctx {int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *hantro_get_ctrl(struct hantro_ctx *ctx, u32 id)
{
	struct v4l2_ctrl *ctrl;

	ctrl = v4l2_ctrl_find(&ctx->ctrl_handler, id);
	return ctrl ? ctrl->p_cur.p : NULL;
}