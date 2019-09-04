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
typedef  int u64 ;
typedef  int s64 ;
typedef  enum v4l2_ctrl_type { ____Placeholder_v4l2_ctrl_type } v4l2_ctrl_type ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
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

__attribute__((used)) static int check_range(enum v4l2_ctrl_type type,
		s64 min, s64 max, u64 step, s64 def)
{
	switch (type) {
	case V4L2_CTRL_TYPE_BOOLEAN:
		if (step != 1 || max > 1 || min < 0)
			return -ERANGE;
		/* fall through */
	case V4L2_CTRL_TYPE_U8:
	case V4L2_CTRL_TYPE_U16:
	case V4L2_CTRL_TYPE_U32:
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_INTEGER64:
		if (step == 0 || min > max || def < min || def > max)
			return -ERANGE;
		return 0;
	case V4L2_CTRL_TYPE_BITMASK:
		if (step || min || !max || (def & ~max))
			return -ERANGE;
		return 0;
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		if (min > max || def < min || def > max)
			return -ERANGE;
		/* Note: step == menu_skip_mask for menu controls.
		   So here we check if the default value is masked out. */
		if (step && ((1 << def) & step))
			return -EINVAL;
		return 0;
	case V4L2_CTRL_TYPE_STRING:
		if (min > max || min < 0 || step < 1 || def)
			return -ERANGE;
		return 0;
	default:
		return 0;
	}
}