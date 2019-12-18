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
struct v4l2_queryctrl {int /*<<< orphan*/  default_value; int /*<<< orphan*/  step; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct v4l2_query_ext_ctrl {int /*<<< orphan*/  default_value; int /*<<< orphan*/  step; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  id; int /*<<< orphan*/  member_0; } ;
struct v4l2_ctrl_handler {int dummy; } ;

/* Variables and functions */
#define  V4L2_CTRL_TYPE_BITMASK 133 
#define  V4L2_CTRL_TYPE_BOOLEAN 132 
#define  V4L2_CTRL_TYPE_INTEGER 131 
#define  V4L2_CTRL_TYPE_INTEGER_MENU 130 
#define  V4L2_CTRL_TYPE_MENU 129 
#define  V4L2_CTRL_TYPE_STRING 128 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int v4l2_query_ext_ctrl (struct v4l2_ctrl_handler*,struct v4l2_query_ext_ctrl*) ; 

int v4l2_queryctrl(struct v4l2_ctrl_handler *hdl, struct v4l2_queryctrl *qc)
{
	struct v4l2_query_ext_ctrl qec = { qc->id };
	int rc;

	rc = v4l2_query_ext_ctrl(hdl, &qec);
	if (rc)
		return rc;

	qc->id = qec.id;
	qc->type = qec.type;
	qc->flags = qec.flags;
	strscpy(qc->name, qec.name, sizeof(qc->name));
	switch (qc->type) {
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_BOOLEAN:
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
	case V4L2_CTRL_TYPE_STRING:
	case V4L2_CTRL_TYPE_BITMASK:
		qc->minimum = qec.minimum;
		qc->maximum = qec.maximum;
		qc->step = qec.step;
		qc->default_value = qec.default_value;
		break;
	default:
		qc->minimum = 0;
		qc->maximum = 0;
		qc->step = 0;
		qc->default_value = 0;
		break;
	}
	return 0;
}