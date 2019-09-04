#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_queryctrl {int /*<<< orphan*/  default_value; int /*<<< orphan*/  step; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  default_value; int /*<<< orphan*/  step; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  changes; int /*<<< orphan*/  value; } ;
struct TYPE_4__ {TYPE_1__ ctrl; } ;
struct v4l2_event {TYPE_2__ u; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct uvc_video_chain {int dummy; } ;
struct uvc_control_mapping {int dummy; } ;
struct uvc_control {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_EVENT_CTRL ; 
 int /*<<< orphan*/  __uvc_query_v4l2_ctrl (struct uvc_video_chain*,struct uvc_control*,struct uvc_control_mapping*,struct v4l2_queryctrl*) ; 
 int /*<<< orphan*/  memset (struct v4l2_event*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uvc_ctrl_fill_event(struct uvc_video_chain *chain,
	struct v4l2_event *ev,
	struct uvc_control *ctrl,
	struct uvc_control_mapping *mapping,
	s32 value, u32 changes)
{
	struct v4l2_queryctrl v4l2_ctrl;

	__uvc_query_v4l2_ctrl(chain, ctrl, mapping, &v4l2_ctrl);

	memset(ev, 0, sizeof(*ev));
	ev->type = V4L2_EVENT_CTRL;
	ev->id = v4l2_ctrl.id;
	ev->u.ctrl.value = value;
	ev->u.ctrl.changes = changes;
	ev->u.ctrl.type = v4l2_ctrl.type;
	ev->u.ctrl.flags = v4l2_ctrl.flags;
	ev->u.ctrl.minimum = v4l2_ctrl.minimum;
	ev->u.ctrl.maximum = v4l2_ctrl.maximum;
	ev->u.ctrl.step = v4l2_ctrl.step;
	ev->u.ctrl.default_value = v4l2_ctrl.default_value;
}