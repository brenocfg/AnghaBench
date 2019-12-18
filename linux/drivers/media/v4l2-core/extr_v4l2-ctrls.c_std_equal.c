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
union v4l2_ctrl_ptr {size_t p_char; size_t p; int /*<<< orphan*/ * p_s32; int /*<<< orphan*/ * p_u32; int /*<<< orphan*/ * p_u16; int /*<<< orphan*/ * p_u8; int /*<<< orphan*/ * p_s64; } ;
typedef  size_t u32 ;
struct v4l2_ctrl {int type; size_t elem_size; int /*<<< orphan*/  is_int; } ;

/* Variables and functions */
#define  V4L2_CTRL_TYPE_BUTTON 133 
#define  V4L2_CTRL_TYPE_INTEGER64 132 
#define  V4L2_CTRL_TYPE_STRING 131 
#define  V4L2_CTRL_TYPE_U16 130 
#define  V4L2_CTRL_TYPE_U32 129 
#define  V4L2_CTRL_TYPE_U8 128 
 int /*<<< orphan*/  memcmp (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  strcmp (size_t,size_t) ; 

__attribute__((used)) static bool std_equal(const struct v4l2_ctrl *ctrl, u32 idx,
		      union v4l2_ctrl_ptr ptr1,
		      union v4l2_ctrl_ptr ptr2)
{
	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_BUTTON:
		return false;
	case V4L2_CTRL_TYPE_STRING:
		idx *= ctrl->elem_size;
		/* strings are always 0-terminated */
		return !strcmp(ptr1.p_char + idx, ptr2.p_char + idx);
	case V4L2_CTRL_TYPE_INTEGER64:
		return ptr1.p_s64[idx] == ptr2.p_s64[idx];
	case V4L2_CTRL_TYPE_U8:
		return ptr1.p_u8[idx] == ptr2.p_u8[idx];
	case V4L2_CTRL_TYPE_U16:
		return ptr1.p_u16[idx] == ptr2.p_u16[idx];
	case V4L2_CTRL_TYPE_U32:
		return ptr1.p_u32[idx] == ptr2.p_u32[idx];
	default:
		if (ctrl->is_int)
			return ptr1.p_s32[idx] == ptr2.p_s32[idx];
		idx *= ctrl->elem_size;
		return !memcmp(ptr1.p + idx, ptr2.p + idx, ctrl->elem_size);
	}
}