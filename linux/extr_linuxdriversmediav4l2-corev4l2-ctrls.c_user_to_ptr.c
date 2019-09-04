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
union v4l2_ctrl_ptr {char* p; char* p_char; int /*<<< orphan*/ * p_s32; int /*<<< orphan*/ * p_s64; } ;
typedef  unsigned int u32 ;
struct v4l2_ext_control {unsigned int size; int /*<<< orphan*/  value; int /*<<< orphan*/  string; int /*<<< orphan*/  value64; int /*<<< orphan*/  ptr; } ;
struct v4l2_ctrl {int is_new; unsigned int elem_size; unsigned int elems; int type; int /*<<< orphan*/  maximum; TYPE_1__* type_ops; int /*<<< orphan*/  is_array; int /*<<< orphan*/  is_string; scalar_t__ is_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct v4l2_ctrl*,unsigned int,union v4l2_ctrl_ptr) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int ERANGE ; 
#define  V4L2_CTRL_TYPE_INTEGER64 129 
#define  V4L2_CTRL_TYPE_STRING 128 
 scalar_t__ copy_from_user (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_ctrl*,unsigned int,union v4l2_ctrl_ptr) ; 

__attribute__((used)) static int user_to_ptr(struct v4l2_ext_control *c,
		       struct v4l2_ctrl *ctrl,
		       union v4l2_ctrl_ptr ptr)
{
	int ret;
	u32 size;

	ctrl->is_new = 1;
	if (ctrl->is_ptr && !ctrl->is_string) {
		unsigned idx;

		ret = copy_from_user(ptr.p, c->ptr, c->size) ? -EFAULT : 0;
		if (ret || !ctrl->is_array)
			return ret;
		for (idx = c->size / ctrl->elem_size; idx < ctrl->elems; idx++)
			ctrl->type_ops->init(ctrl, idx, ptr);
		return 0;
	}

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_INTEGER64:
		*ptr.p_s64 = c->value64;
		break;
	case V4L2_CTRL_TYPE_STRING:
		size = c->size;
		if (size == 0)
			return -ERANGE;
		if (size > ctrl->maximum + 1)
			size = ctrl->maximum + 1;
		ret = copy_from_user(ptr.p_char, c->string, size) ? -EFAULT : 0;
		if (!ret) {
			char last = ptr.p_char[size - 1];

			ptr.p_char[size - 1] = 0;
			/* If the string was longer than ctrl->maximum,
			   then return an error. */
			if (strlen(ptr.p_char) == ctrl->maximum && last)
				return -ERANGE;
		}
		return ret;
	default:
		*ptr.p_s32 = c->value;
		break;
	}
	return 0;
}