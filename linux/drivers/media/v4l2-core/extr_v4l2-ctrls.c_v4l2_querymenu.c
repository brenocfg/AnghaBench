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
typedef  unsigned long long u32 ;
struct v4l2_querymenu {unsigned long long index; int /*<<< orphan*/  value; int /*<<< orphan*/  name; scalar_t__ reserved; int /*<<< orphan*/  id; } ;
struct v4l2_ctrl_handler {int dummy; } ;
struct v4l2_ctrl {int type; char** qmenu; unsigned long long minimum; unsigned long long maximum; unsigned long long menu_skip_mask; int /*<<< orphan*/ * qmenu_int; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CTRL_TYPE_INTEGER_MENU 129 
#define  V4L2_CTRL_TYPE_MENU 128 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ) ; 

int v4l2_querymenu(struct v4l2_ctrl_handler *hdl, struct v4l2_querymenu *qm)
{
	struct v4l2_ctrl *ctrl;
	u32 i = qm->index;

	ctrl = v4l2_ctrl_find(hdl, qm->id);
	if (!ctrl)
		return -EINVAL;

	qm->reserved = 0;
	/* Sanity checks */
	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_MENU:
		if (ctrl->qmenu == NULL)
			return -EINVAL;
		break;
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		if (ctrl->qmenu_int == NULL)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	if (i < ctrl->minimum || i > ctrl->maximum)
		return -EINVAL;

	/* Use mask to see if this menu item should be skipped */
	if (ctrl->menu_skip_mask & (1ULL << i))
		return -EINVAL;
	/* Empty menu items should also be skipped */
	if (ctrl->type == V4L2_CTRL_TYPE_MENU) {
		if (ctrl->qmenu[i] == NULL || ctrl->qmenu[i][0] == '\0')
			return -EINVAL;
		strscpy(qm->name, ctrl->qmenu[i], sizeof(qm->name));
	} else {
		qm->value = ctrl->qmenu_int[i];
	}
	return 0;
}