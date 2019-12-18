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
typedef  scalar_t__ u8 ;
struct pci_dev {scalar_t__ pcie_mpss; scalar_t__ is_hotplug_bridge; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 

__attribute__((used)) static int pcie_find_smpss(struct pci_dev *dev, void *data)
{
	u8 *smpss = data;

	if (!pci_is_pcie(dev))
		return 0;

	/*
	 * We don't have a way to change MPS settings on devices that have
	 * drivers attached.  A hot-added device might support only the minimum
	 * MPS setting (MPS=128).  Therefore, if the fabric contains a bridge
	 * where devices may be hot-added, we limit the fabric MPS to 128 so
	 * hot-added devices will work correctly.
	 *
	 * However, if we hot-add a device to a slot directly below a Root
	 * Port, it's impossible for there to be other existing devices below
	 * the port.  We don't limit the MPS in this case because we can
	 * reconfigure MPS on both the Root Port and the hot-added device,
	 * and there are no other devices involved.
	 *
	 * Note that this PCIE_BUS_SAFE path assumes no peer-to-peer DMA.
	 */
	if (dev->is_hotplug_bridge &&
	    pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		*smpss = 0;

	if (*smpss > dev->pcie_mpss)
		*smpss = dev->pcie_mpss;

	return 0;
}