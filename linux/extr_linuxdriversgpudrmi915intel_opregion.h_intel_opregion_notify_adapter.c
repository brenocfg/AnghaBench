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
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */

__attribute__((used)) static inline int
intel_opregion_notify_adapter(struct drm_i915_private *dev, pci_power_t state)
{
	return 0;
}