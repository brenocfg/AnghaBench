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
struct drm_panel {TYPE_1__* funcs; } ;
struct TYPE_2__ {int (* enable ) (struct drm_panel*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int stub1 (struct drm_panel*) ; 

int drm_panel_enable(struct drm_panel *panel)
{
	if (panel && panel->funcs && panel->funcs->enable)
		return panel->funcs->enable(panel);

	return panel ? -ENOSYS : -EINVAL;
}