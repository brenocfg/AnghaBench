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
struct uvc_device {int dummy; } ;
struct uvc_control_mapping {scalar_t__ selector; int /*<<< orphan*/  entity; } ;
struct uvc_control_info {scalar_t__ index; int /*<<< orphan*/  entity; } ;
struct TYPE_2__ {scalar_t__ selector; } ;
struct uvc_control {scalar_t__ index; TYPE_1__ info; int /*<<< orphan*/  entity; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int ARRAY_SIZE (void*) ; 
 scalar_t__ UVC_ENTITY_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ UVC_VC_EXTENSION_UNIT ; 
 int /*<<< orphan*/  __uvc_ctrl_add_mapping (struct uvc_device*,struct uvc_control*,struct uvc_control_mapping const*) ; 
 int /*<<< orphan*/  uvc_ctrl_add_info (struct uvc_device*,struct uvc_control*,struct uvc_control_info const*) ; 
 void* uvc_ctrl_mappings ; 
 void* uvc_ctrls ; 
 scalar_t__ uvc_entity_match_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvc_ctrl_init_ctrl(struct uvc_device *dev, struct uvc_control *ctrl)
{
	const struct uvc_control_info *info = uvc_ctrls;
	const struct uvc_control_info *iend = info + ARRAY_SIZE(uvc_ctrls);
	const struct uvc_control_mapping *mapping = uvc_ctrl_mappings;
	const struct uvc_control_mapping *mend =
		mapping + ARRAY_SIZE(uvc_ctrl_mappings);

	/* XU controls initialization requires querying the device for control
	 * information. As some buggy UVC devices will crash when queried
	 * repeatedly in a tight loop, delay XU controls initialization until
	 * first use.
	 */
	if (UVC_ENTITY_TYPE(ctrl->entity) == UVC_VC_EXTENSION_UNIT)
		return;

	for (; info < iend; ++info) {
		if (uvc_entity_match_guid(ctrl->entity, info->entity) &&
		    ctrl->index == info->index) {
			uvc_ctrl_add_info(dev, ctrl, info);
			break;
		 }
	}

	if (!ctrl->initialized)
		return;

	for (; mapping < mend; ++mapping) {
		if (uvc_entity_match_guid(ctrl->entity, mapping->entity) &&
		    ctrl->info.selector == mapping->selector)
			__uvc_ctrl_add_mapping(dev, ctrl, mapping);
	}
}