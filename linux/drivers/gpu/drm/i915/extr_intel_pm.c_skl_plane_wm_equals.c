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
struct skl_plane_wm {int /*<<< orphan*/  trans_wm; int /*<<< orphan*/ * uv_wm; int /*<<< orphan*/ * wm; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ilk_wm_max_level (struct drm_i915_private*) ; 
 int skl_wm_level_equals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool skl_plane_wm_equals(struct drm_i915_private *dev_priv,
				const struct skl_plane_wm *wm1,
				const struct skl_plane_wm *wm2)
{
	int level, max_level = ilk_wm_max_level(dev_priv);

	for (level = 0; level <= max_level; level++) {
		if (!skl_wm_level_equals(&wm1->wm[level], &wm2->wm[level]) ||
		    !skl_wm_level_equals(&wm1->uv_wm[level], &wm2->uv_wm[level]))
			return false;
	}

	return skl_wm_level_equals(&wm1->trans_wm, &wm2->trans_wm);
}