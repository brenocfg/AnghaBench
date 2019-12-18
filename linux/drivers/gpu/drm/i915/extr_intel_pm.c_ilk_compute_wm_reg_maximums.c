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
struct ilk_wm_maximums {int /*<<< orphan*/  fbc; int /*<<< orphan*/  cur; void* spr; void* pri; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ilk_cursor_wm_reg_max (struct drm_i915_private const*,int) ; 
 int /*<<< orphan*/  ilk_fbc_wm_reg_max (struct drm_i915_private const*) ; 
 void* ilk_plane_wm_reg_max (struct drm_i915_private const*,int,int) ; 

__attribute__((used)) static void ilk_compute_wm_reg_maximums(const struct drm_i915_private *dev_priv,
					int level,
					struct ilk_wm_maximums *max)
{
	max->pri = ilk_plane_wm_reg_max(dev_priv, level, false);
	max->spr = ilk_plane_wm_reg_max(dev_priv, level, true);
	max->cur = ilk_cursor_wm_reg_max(dev_priv, level);
	max->fbc = ilk_fbc_wm_reg_max(dev_priv);
}