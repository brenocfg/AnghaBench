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
struct v4l2_ctrl_ref {struct v4l2_ctrl_ref* req; int /*<<< orphan*/  p_req; TYPE_1__* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptr_to_ptr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void new_to_req(struct v4l2_ctrl_ref *ref)
{
	if (!ref)
		return;
	ptr_to_ptr(ref->ctrl, ref->ctrl->p_new, ref->p_req);
	ref->req = ref;
}