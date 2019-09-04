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
union v4l2_ctrl_ptr {int /*<<< orphan*/ * p_s32; int /*<<< orphan*/ * p_s64; int /*<<< orphan*/  p_char; int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ext_control {int /*<<< orphan*/  value; int /*<<< orphan*/  value64; int /*<<< orphan*/  string; int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
struct v4l2_ctrl {int type; int /*<<< orphan*/  elem_size; int /*<<< orphan*/  is_string; scalar_t__ is_ptr; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOSPC ; 
#define  V4L2_CTRL_TYPE_INTEGER64 129 
#define  V4L2_CTRL_TYPE_STRING 128 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ptr_to_user(struct v4l2_ext_control *c,
		       struct v4l2_ctrl *ctrl,
		       union v4l2_ctrl_ptr ptr)
{
	u32 len;

	if (ctrl->is_ptr && !ctrl->is_string)
		return copy_to_user(c->ptr, ptr.p, c->size) ?
		       -EFAULT : 0;

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_STRING:
		len = strlen(ptr.p_char);
		if (c->size < len + 1) {
			c->size = ctrl->elem_size;
			return -ENOSPC;
		}
		return copy_to_user(c->string, ptr.p_char, len + 1) ?
		       -EFAULT : 0;
	case V4L2_CTRL_TYPE_INTEGER64:
		c->value64 = *ptr.p_s64;
		break;
	default:
		c->value = *ptr.p_s32;
		break;
	}
	return 0;
}