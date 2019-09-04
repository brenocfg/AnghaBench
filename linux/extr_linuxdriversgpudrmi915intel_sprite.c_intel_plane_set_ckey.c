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
struct drm_intel_sprite_colorkey {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  plane; } ;
struct intel_plane_state {struct drm_intel_sprite_colorkey ckey; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {scalar_t__ id; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int I915_SET_COLORKEY_DESTINATION ; 
 int I915_SET_COLORKEY_SOURCE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ PLANE_PRIMARY ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_plane_set_ckey(struct intel_plane_state *plane_state,
				 const struct drm_intel_sprite_colorkey *set)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	struct drm_intel_sprite_colorkey *key = &plane_state->ckey;

	*key = *set;

	/*
	 * We want src key enabled on the
	 * sprite and not on the primary.
	 */
	if (plane->id == PLANE_PRIMARY &&
	    set->flags & I915_SET_COLORKEY_SOURCE)
		key->flags = 0;

	/*
	 * On SKL+ we want dst key enabled on
	 * the primary and not on the sprite.
	 */
	if (INTEL_GEN(dev_priv) >= 9 && plane->id != PLANE_PRIMARY &&
	    set->flags & I915_SET_COLORKEY_DESTINATION)
		key->flags = 0;
}