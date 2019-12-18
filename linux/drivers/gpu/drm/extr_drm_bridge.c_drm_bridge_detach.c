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
struct drm_bridge {int /*<<< orphan*/ * dev; TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach ) (struct drm_bridge*) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct drm_bridge*) ; 

void drm_bridge_detach(struct drm_bridge *bridge)
{
	if (WARN_ON(!bridge))
		return;

	if (WARN_ON(!bridge->dev))
		return;

	if (bridge->funcs->detach)
		bridge->funcs->detach(bridge);

	bridge->dev = NULL;
}