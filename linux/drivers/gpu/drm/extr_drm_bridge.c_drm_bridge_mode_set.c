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
struct drm_display_mode {int dummy; } ;
struct drm_bridge {struct drm_bridge* next; TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mode_set ) (struct drm_bridge*,struct drm_display_mode const*,struct drm_display_mode const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_bridge*,struct drm_display_mode const*,struct drm_display_mode const*) ; 

void drm_bridge_mode_set(struct drm_bridge *bridge,
			 const struct drm_display_mode *mode,
			 const struct drm_display_mode *adjusted_mode)
{
	if (!bridge)
		return;

	if (bridge->funcs->mode_set)
		bridge->funcs->mode_set(bridge, mode, adjusted_mode);

	drm_bridge_mode_set(bridge->next, mode, adjusted_mode);
}