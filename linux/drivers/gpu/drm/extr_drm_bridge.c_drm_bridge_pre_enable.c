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
struct drm_bridge {TYPE_1__* funcs; struct drm_bridge* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pre_enable ) (struct drm_bridge*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_bridge*) ; 

void drm_bridge_pre_enable(struct drm_bridge *bridge)
{
	if (!bridge)
		return;

	drm_bridge_pre_enable(bridge->next);

	if (bridge->funcs->pre_enable)
		bridge->funcs->pre_enable(bridge);
}