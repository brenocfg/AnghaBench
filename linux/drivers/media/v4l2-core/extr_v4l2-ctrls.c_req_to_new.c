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
struct v4l2_ctrl_ref {TYPE_2__* ctrl; TYPE_1__* req; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_new; int /*<<< orphan*/  p_cur; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptr_to_ptr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void req_to_new(struct v4l2_ctrl_ref *ref)
{
	if (!ref)
		return;
	if (ref->req)
		ptr_to_ptr(ref->ctrl, ref->req->p_req, ref->ctrl->p_new);
	else
		ptr_to_ptr(ref->ctrl, ref->ctrl->p_cur, ref->ctrl->p_new);
}