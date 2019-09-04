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
struct intel_device_info {int dummy; } ;
struct drm_i915_private {struct intel_device_info const info; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct intel_device_info *
intel_info(const struct drm_i915_private *dev_priv)
{
	return &dev_priv->info;
}