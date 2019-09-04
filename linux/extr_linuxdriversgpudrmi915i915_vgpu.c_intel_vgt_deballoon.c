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
struct drm_i915_private {int /*<<< orphan*/  ggtt; } ;
struct TYPE_2__ {int /*<<< orphan*/ * space; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 TYPE_1__ bl_info ; 
 int /*<<< orphan*/  intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vgt_deballoon_space (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void intel_vgt_deballoon(struct drm_i915_private *dev_priv)
{
	int i;

	if (!intel_vgpu_active(dev_priv))
		return;

	DRM_DEBUG("VGT deballoon.\n");

	for (i = 0; i < 4; i++)
		vgt_deballoon_space(&dev_priv->ggtt, &bl_info.space[i]);
}