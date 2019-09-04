#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_5__ {scalar_t__* p_s64; scalar_t__* p_s32; } ;
struct TYPE_6__ {scalar_t__* p_s64; scalar_t__* p_s32; } ;
struct v4l2_ctrl {int type; scalar_t__ minimum; scalar_t__ maximum; scalar_t__ step; scalar_t__ default_value; TYPE_2__ p_cur; TYPE_3__ p_new; int /*<<< orphan*/  is_array; TYPE_1__* handler; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CTRL_TYPE_BITMASK 136 
#define  V4L2_CTRL_TYPE_BOOLEAN 135 
#define  V4L2_CTRL_TYPE_INTEGER 134 
#define  V4L2_CTRL_TYPE_INTEGER64 133 
#define  V4L2_CTRL_TYPE_INTEGER_MENU 132 
#define  V4L2_CTRL_TYPE_MENU 131 
#define  V4L2_CTRL_TYPE_U16 130 
#define  V4L2_CTRL_TYPE_U32 129 
#define  V4L2_CTRL_TYPE_U8 128 
 int /*<<< orphan*/  V4L2_EVENT_CTRL_CH_RANGE ; 
 int check_range (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cur_to_new (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_event (int /*<<< orphan*/ *,struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 
 int set_ctrl (int /*<<< orphan*/ *,struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 
 scalar_t__ validate_new (struct v4l2_ctrl*,TYPE_3__) ; 

int __v4l2_ctrl_modify_range(struct v4l2_ctrl *ctrl,
			s64 min, s64 max, u64 step, s64 def)
{
	bool value_changed;
	bool range_changed = false;
	int ret;

	lockdep_assert_held(ctrl->handler->lock);

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_INTEGER64:
	case V4L2_CTRL_TYPE_BOOLEAN:
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
	case V4L2_CTRL_TYPE_BITMASK:
	case V4L2_CTRL_TYPE_U8:
	case V4L2_CTRL_TYPE_U16:
	case V4L2_CTRL_TYPE_U32:
		if (ctrl->is_array)
			return -EINVAL;
		ret = check_range(ctrl->type, min, max, step, def);
		if (ret)
			return ret;
		break;
	default:
		return -EINVAL;
	}
	if ((ctrl->minimum != min) || (ctrl->maximum != max) ||
		(ctrl->step != step) || ctrl->default_value != def) {
		range_changed = true;
		ctrl->minimum = min;
		ctrl->maximum = max;
		ctrl->step = step;
		ctrl->default_value = def;
	}
	cur_to_new(ctrl);
	if (validate_new(ctrl, ctrl->p_new)) {
		if (ctrl->type == V4L2_CTRL_TYPE_INTEGER64)
			*ctrl->p_new.p_s64 = def;
		else
			*ctrl->p_new.p_s32 = def;
	}

	if (ctrl->type == V4L2_CTRL_TYPE_INTEGER64)
		value_changed = *ctrl->p_new.p_s64 != *ctrl->p_cur.p_s64;
	else
		value_changed = *ctrl->p_new.p_s32 != *ctrl->p_cur.p_s32;
	if (value_changed)
		ret = set_ctrl(NULL, ctrl, V4L2_EVENT_CTRL_CH_RANGE);
	else if (range_changed)
		send_event(NULL, ctrl, V4L2_EVENT_CTRL_CH_RANGE);
	return ret;
}