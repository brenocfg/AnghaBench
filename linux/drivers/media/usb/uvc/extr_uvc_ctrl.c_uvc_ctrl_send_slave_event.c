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
typedef  int /*<<< orphan*/  u32 ;
struct uvc_video_chain {int dummy; } ;
struct uvc_fh {int dummy; } ;
struct uvc_control_mapping {int dummy; } ;
struct uvc_control {int /*<<< orphan*/  entity; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_EVENT_CTRL_CH_FLAGS ; 
 int /*<<< orphan*/  V4L2_EVENT_CTRL_CH_VALUE ; 
 scalar_t__ __uvc_ctrl_get (struct uvc_video_chain*,struct uvc_control*,struct uvc_control_mapping*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __uvc_find_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uvc_control_mapping**,struct uvc_control**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_ctrl_send_event (struct uvc_video_chain*,struct uvc_fh*,struct uvc_control*,struct uvc_control_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvc_ctrl_send_slave_event(struct uvc_video_chain *chain,
	struct uvc_fh *handle, struct uvc_control *master, u32 slave_id)
{
	struct uvc_control_mapping *mapping = NULL;
	struct uvc_control *ctrl = NULL;
	u32 changes = V4L2_EVENT_CTRL_CH_FLAGS;
	s32 val = 0;

	__uvc_find_control(master->entity, slave_id, &mapping, &ctrl, 0);
	if (ctrl == NULL)
		return;

	if (__uvc_ctrl_get(chain, ctrl, mapping, &val) == 0)
		changes |= V4L2_EVENT_CTRL_CH_VALUE;

	uvc_ctrl_send_event(chain, handle, ctrl, mapping, val, changes);
}