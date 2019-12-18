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
struct drm_atomic_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pre_enable ) (struct drm_bridge*) ;int /*<<< orphan*/  (* atomic_pre_enable ) (struct drm_bridge*,struct drm_atomic_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_bridge*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  stub2 (struct drm_bridge*) ; 

void drm_atomic_bridge_pre_enable(struct drm_bridge *bridge,
				  struct drm_atomic_state *state)
{
	if (!bridge)
		return;

	drm_atomic_bridge_pre_enable(bridge->next, state);

	if (bridge->funcs->atomic_pre_enable)
		bridge->funcs->atomic_pre_enable(bridge, state);
	else if (bridge->funcs->pre_enable)
		bridge->funcs->pre_enable(bridge);
}