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
struct v4l2_ext_control {int dummy; } ;
struct v4l2_ctrl_ref {int /*<<< orphan*/  p_req; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int ptr_to_user (struct v4l2_ext_control*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int req_to_user(struct v4l2_ext_control *c,
		       struct v4l2_ctrl_ref *ref)
{
	return ptr_to_user(c, ref->ctrl, ref->p_req);
}