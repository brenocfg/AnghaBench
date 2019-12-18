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
struct v4l2_queryctrl {int type; unsigned int default_value; unsigned int minimum; int maximum; int step; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct uvc_video_chain {int dummy; } ;
struct uvc_menu_info {unsigned int value; } ;
struct uvc_control_mapping {int v4l2_type; scalar_t__ master_manual; unsigned int (* get ) (struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;unsigned int menu_count; struct uvc_menu_info* menu_info; scalar_t__ master_id; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int flags; } ;
struct uvc_control {TYPE_1__ info; int /*<<< orphan*/  cached; int /*<<< orphan*/  entity; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_CTRL_DATA_DEF ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_MAX ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_MIN ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_RES ; 
 int UVC_CTRL_FLAG_GET_CUR ; 
 int UVC_CTRL_FLAG_GET_DEF ; 
 int UVC_CTRL_FLAG_GET_MAX ; 
 int UVC_CTRL_FLAG_GET_MIN ; 
 int UVC_CTRL_FLAG_GET_RES ; 
 int UVC_CTRL_FLAG_SET_CUR ; 
 int /*<<< orphan*/  UVC_GET_DEF ; 
 int /*<<< orphan*/  UVC_GET_MAX ; 
 int /*<<< orphan*/  UVC_GET_MIN ; 
 int /*<<< orphan*/  UVC_GET_RES ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_INACTIVE ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_READ_ONLY ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_WRITE_ONLY ; 
#define  V4L2_CTRL_TYPE_BOOLEAN 130 
#define  V4L2_CTRL_TYPE_BUTTON 129 
#define  V4L2_CTRL_TYPE_MENU 128 
 int __uvc_ctrl_get (struct uvc_video_chain*,struct uvc_control*,struct uvc_control_mapping*,scalar_t__*) ; 
 int /*<<< orphan*/  __uvc_find_control (int /*<<< orphan*/ ,scalar_t__,struct uvc_control_mapping**,struct uvc_control**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_queryctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int stub1 (struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub3 (struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub4 (struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_ctrl_data (struct uvc_control*,int /*<<< orphan*/ ) ; 
 int uvc_ctrl_populate_cache (struct uvc_video_chain*,struct uvc_control*) ; 

__attribute__((used)) static int __uvc_query_v4l2_ctrl(struct uvc_video_chain *chain,
	struct uvc_control *ctrl,
	struct uvc_control_mapping *mapping,
	struct v4l2_queryctrl *v4l2_ctrl)
{
	struct uvc_control_mapping *master_map = NULL;
	struct uvc_control *master_ctrl = NULL;
	const struct uvc_menu_info *menu;
	unsigned int i;

	memset(v4l2_ctrl, 0, sizeof(*v4l2_ctrl));
	v4l2_ctrl->id = mapping->id;
	v4l2_ctrl->type = mapping->v4l2_type;
	strscpy(v4l2_ctrl->name, mapping->name, sizeof(v4l2_ctrl->name));
	v4l2_ctrl->flags = 0;

	if (!(ctrl->info.flags & UVC_CTRL_FLAG_GET_CUR))
		v4l2_ctrl->flags |= V4L2_CTRL_FLAG_WRITE_ONLY;
	if (!(ctrl->info.flags & UVC_CTRL_FLAG_SET_CUR))
		v4l2_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	if (mapping->master_id)
		__uvc_find_control(ctrl->entity, mapping->master_id,
				   &master_map, &master_ctrl, 0);
	if (master_ctrl && (master_ctrl->info.flags & UVC_CTRL_FLAG_GET_CUR)) {
		s32 val;
		int ret = __uvc_ctrl_get(chain, master_ctrl, master_map, &val);
		if (ret < 0)
			return ret;

		if (val != mapping->master_manual)
				v4l2_ctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
	}

	if (!ctrl->cached) {
		int ret = uvc_ctrl_populate_cache(chain, ctrl);
		if (ret < 0)
			return ret;
	}

	if (ctrl->info.flags & UVC_CTRL_FLAG_GET_DEF) {
		v4l2_ctrl->default_value = mapping->get(mapping, UVC_GET_DEF,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_DEF));
	}

	switch (mapping->v4l2_type) {
	case V4L2_CTRL_TYPE_MENU:
		v4l2_ctrl->minimum = 0;
		v4l2_ctrl->maximum = mapping->menu_count - 1;
		v4l2_ctrl->step = 1;

		menu = mapping->menu_info;
		for (i = 0; i < mapping->menu_count; ++i, ++menu) {
			if (menu->value == v4l2_ctrl->default_value) {
				v4l2_ctrl->default_value = i;
				break;
			}
		}

		return 0;

	case V4L2_CTRL_TYPE_BOOLEAN:
		v4l2_ctrl->minimum = 0;
		v4l2_ctrl->maximum = 1;
		v4l2_ctrl->step = 1;
		return 0;

	case V4L2_CTRL_TYPE_BUTTON:
		v4l2_ctrl->minimum = 0;
		v4l2_ctrl->maximum = 0;
		v4l2_ctrl->step = 0;
		return 0;

	default:
		break;
	}

	if (ctrl->info.flags & UVC_CTRL_FLAG_GET_MIN)
		v4l2_ctrl->minimum = mapping->get(mapping, UVC_GET_MIN,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MIN));

	if (ctrl->info.flags & UVC_CTRL_FLAG_GET_MAX)
		v4l2_ctrl->maximum = mapping->get(mapping, UVC_GET_MAX,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MAX));

	if (ctrl->info.flags & UVC_CTRL_FLAG_GET_RES)
		v4l2_ctrl->step = mapping->get(mapping, UVC_GET_RES,
				  uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES));

	return 0;
}