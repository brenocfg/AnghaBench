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
struct v4l2_ext_control {int dummy; } ;
struct v4l2_ctrl {int elems; int /*<<< orphan*/  p_new; TYPE_1__* type_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct v4l2_ctrl*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ptr_to_user (struct v4l2_ext_control*,struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_ctrl*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int def_to_user(struct v4l2_ext_control *c, struct v4l2_ctrl *ctrl)
{
	int idx;

	for (idx = 0; idx < ctrl->elems; idx++)
		ctrl->type_ops->init(ctrl, idx, ctrl->p_new);

	return ptr_to_user(c, ctrl, ctrl->p_new);
}