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
union v4l2_ctrl_ptr {unsigned int* p_s32; unsigned int* p_s64; unsigned int p_char; int /*<<< orphan*/ * p_u32; int /*<<< orphan*/ * p_u16; int /*<<< orphan*/ * p_u8; } ;
struct v4l2_ctrl {unsigned int nr_of_dims; unsigned int* dims; int type; unsigned int* qmenu; unsigned int* qmenu_int; scalar_t__ is_array; union v4l2_ctrl_ptr p_cur; } ;

/* Variables and functions */
#define  V4L2_CTRL_TYPE_BITMASK 137 
#define  V4L2_CTRL_TYPE_BOOLEAN 136 
#define  V4L2_CTRL_TYPE_INTEGER 135 
#define  V4L2_CTRL_TYPE_INTEGER64 134 
#define  V4L2_CTRL_TYPE_INTEGER_MENU 133 
#define  V4L2_CTRL_TYPE_MENU 132 
#define  V4L2_CTRL_TYPE_STRING 131 
#define  V4L2_CTRL_TYPE_U16 130 
#define  V4L2_CTRL_TYPE_U32 129 
#define  V4L2_CTRL_TYPE_U8 128 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void std_log(const struct v4l2_ctrl *ctrl)
{
	union v4l2_ctrl_ptr ptr = ctrl->p_cur;

	if (ctrl->is_array) {
		unsigned i;

		for (i = 0; i < ctrl->nr_of_dims; i++)
			pr_cont("[%u]", ctrl->dims[i]);
		pr_cont(" ");
	}

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_INTEGER:
		pr_cont("%d", *ptr.p_s32);
		break;
	case V4L2_CTRL_TYPE_BOOLEAN:
		pr_cont("%s", *ptr.p_s32 ? "true" : "false");
		break;
	case V4L2_CTRL_TYPE_MENU:
		pr_cont("%s", ctrl->qmenu[*ptr.p_s32]);
		break;
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		pr_cont("%lld", ctrl->qmenu_int[*ptr.p_s32]);
		break;
	case V4L2_CTRL_TYPE_BITMASK:
		pr_cont("0x%08x", *ptr.p_s32);
		break;
	case V4L2_CTRL_TYPE_INTEGER64:
		pr_cont("%lld", *ptr.p_s64);
		break;
	case V4L2_CTRL_TYPE_STRING:
		pr_cont("%s", ptr.p_char);
		break;
	case V4L2_CTRL_TYPE_U8:
		pr_cont("%u", (unsigned)*ptr.p_u8);
		break;
	case V4L2_CTRL_TYPE_U16:
		pr_cont("%u", (unsigned)*ptr.p_u16);
		break;
	case V4L2_CTRL_TYPE_U32:
		pr_cont("%u", (unsigned)*ptr.p_u32);
		break;
	default:
		pr_cont("unknown type %d", ctrl->type);
		break;
	}
}