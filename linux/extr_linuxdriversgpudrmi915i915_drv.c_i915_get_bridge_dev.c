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
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct drm_i915_private {int /*<<< orphan*/  bridge_dev; TYPE_2__ drm; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_domain_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_domain_bus_and_slot (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_get_bridge_dev(struct drm_i915_private *dev_priv)
{
	int domain = pci_domain_nr(dev_priv->drm.pdev->bus);

	dev_priv->bridge_dev =
		pci_get_domain_bus_and_slot(domain, 0, PCI_DEVFN(0, 0));
	if (!dev_priv->bridge_dev) {
		DRM_ERROR("bridge device not found\n");
		return -1;
	}
	return 0;
}