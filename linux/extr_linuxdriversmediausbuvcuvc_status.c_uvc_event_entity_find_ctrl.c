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
typedef  scalar_t__ u8 ;
struct uvc_entity {unsigned int ncontrols; struct uvc_control* controls; } ;
struct TYPE_2__ {scalar_t__ selector; } ;
struct uvc_control {TYPE_1__ info; } ;

/* Variables and functions */

__attribute__((used)) static struct uvc_control *uvc_event_entity_find_ctrl(struct uvc_entity *entity,
						      u8 selector)
{
	struct uvc_control *ctrl;
	unsigned int i;

	for (i = 0, ctrl = entity->controls; i < entity->ncontrols; i++, ctrl++)
		if (ctrl->info.selector == selector)
			return ctrl;

	return NULL;
}