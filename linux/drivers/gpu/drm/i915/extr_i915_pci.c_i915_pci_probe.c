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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  device; } ;
struct intel_device_info {scalar_t__ require_force_probe; } ;
struct TYPE_2__ {int /*<<< orphan*/  force_probe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOTTY ; 
 int EPROBE_DEFER ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_driver_probe (struct pci_dev*,struct pci_device_id const*) ; 
 scalar_t__ i915_inject_probe_failure (int /*<<< orphan*/ ) ; 
 int i915_live_selftests (struct pci_dev*) ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  i915_pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ vga_switcheroo_client_probe_defer (struct pci_dev*) ; 

__attribute__((used)) static int i915_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct intel_device_info *intel_info =
		(struct intel_device_info *) ent->driver_data;
	int err;

	if (intel_info->require_force_probe &&
	    !force_probe(pdev->device, i915_modparams.force_probe)) {
		DRM_INFO("Your graphics device %04x is not properly supported by the driver in this\n"
			 "kernel version. To force driver probe anyway, use i915.force_probe=%04x\n"
			 "module parameter or CONFIG_DRM_I915_FORCE_PROBE=%04x configuration option,\n"
			 "or (recommended) check for kernel updates.\n",
			 pdev->device, pdev->device, pdev->device);
		return -ENODEV;
	}

	/* Only bind to function 0 of the device. Early generations
	 * used function 1 as a placeholder for multi-head. This causes
	 * us confusion instead, especially on the systems where both
	 * functions have the same PCI-ID!
	 */
	if (PCI_FUNC(pdev->devfn))
		return -ENODEV;

	/*
	 * apple-gmux is needed on dual GPU MacBook Pro
	 * to probe the panel if we're the inactive GPU.
	 */
	if (vga_switcheroo_client_probe_defer(pdev))
		return -EPROBE_DEFER;

	err = i915_driver_probe(pdev, ent);
	if (err)
		return err;

	if (i915_inject_probe_failure(pci_get_drvdata(pdev))) {
		i915_pci_remove(pdev);
		return -ENODEV;
	}

	err = i915_live_selftests(pdev);
	if (err) {
		i915_pci_remove(pdev);
		return err > 0 ? -ENOTTY : err;
	}

	return 0;
}