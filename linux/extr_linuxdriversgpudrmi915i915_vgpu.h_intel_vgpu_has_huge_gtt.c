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
struct TYPE_2__ {int caps; } ;
struct drm_i915_private {TYPE_1__ vgpu; } ;

/* Variables and functions */
 int VGT_CAPS_HUGE_GTT ; 

__attribute__((used)) static inline bool
intel_vgpu_has_huge_gtt(struct drm_i915_private *dev_priv)
{
	return dev_priv->vgpu.caps & VGT_CAPS_HUGE_GTT;
}