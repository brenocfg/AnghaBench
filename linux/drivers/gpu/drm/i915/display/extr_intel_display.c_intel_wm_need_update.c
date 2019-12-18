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
struct TYPE_4__ {scalar_t__ visible; scalar_t__ rotation; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__* fb; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct TYPE_3__ {scalar_t__ modifier; } ;

/* Variables and functions */
 scalar_t__ drm_rect_height (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_rect_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool intel_wm_need_update(const struct intel_plane_state *cur,
				 struct intel_plane_state *new)
{
	/* Update watermarks on tiling or size changes. */
	if (new->base.visible != cur->base.visible)
		return true;

	if (!cur->base.fb || !new->base.fb)
		return false;

	if (cur->base.fb->modifier != new->base.fb->modifier ||
	    cur->base.rotation != new->base.rotation ||
	    drm_rect_width(&new->base.src) != drm_rect_width(&cur->base.src) ||
	    drm_rect_height(&new->base.src) != drm_rect_height(&cur->base.src) ||
	    drm_rect_width(&new->base.dst) != drm_rect_width(&cur->base.dst) ||
	    drm_rect_height(&new->base.dst) != drm_rect_height(&cur->base.dst))
		return true;

	return false;
}