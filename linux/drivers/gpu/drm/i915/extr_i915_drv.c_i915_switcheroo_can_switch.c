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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ open_count; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 struct drm_i915_private* pdev_to_i915 (struct pci_dev*) ; 

__attribute__((used)) static bool i915_switcheroo_can_switch(struct pci_dev *pdev)
{
	struct drm_i915_private *i915 = pdev_to_i915(pdev);

	/*
	 * FIXME: open_count is protected by drm_global_mutex but that would lead to
	 * locking inversion with the driver load path. And the access here is
	 * completely racy anyway. So don't bother with locking for now.
	 */
	return i915 && i915->drm.open_count == 0;
}