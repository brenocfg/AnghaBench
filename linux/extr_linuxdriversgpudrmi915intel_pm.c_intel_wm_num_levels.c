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
struct TYPE_2__ {int max_level; } ;
struct drm_i915_private {TYPE_1__ wm; } ;

/* Variables and functions */

__attribute__((used)) static int intel_wm_num_levels(struct drm_i915_private *dev_priv)
{
	return dev_priv->wm.max_level + 1;
}