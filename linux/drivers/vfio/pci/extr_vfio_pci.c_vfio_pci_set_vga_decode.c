#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfio_pci_device {struct pci_dev* pdev; } ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_4__ {unsigned char number; } ;

/* Variables and functions */
 int PCI_CLASS_DISPLAY_VGA ; 
 unsigned int VGA_RSRC_LEGACY_IO ; 
 unsigned int VGA_RSRC_LEGACY_MEM ; 
 unsigned int VGA_RSRC_NORMAL_IO ; 
 unsigned int VGA_RSRC_NORMAL_MEM ; 
 unsigned char pci_bus_max_busnr (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 scalar_t__ pci_domain_nr (TYPE_1__*) ; 
 struct pci_dev* pci_get_class (int,struct pci_dev*) ; 
 scalar_t__ pci_is_root_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  vfio_vga_disabled () ; 

__attribute__((used)) static unsigned int vfio_pci_set_vga_decode(void *opaque, bool single_vga)
{
	struct vfio_pci_device *vdev = opaque;
	struct pci_dev *tmp = NULL, *pdev = vdev->pdev;
	unsigned char max_busnr;
	unsigned int decodes;

	if (single_vga || !vfio_vga_disabled() || pci_is_root_bus(pdev->bus))
		return VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM |
		       VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;

	max_busnr = pci_bus_max_busnr(pdev->bus);
	decodes = VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;

	while ((tmp = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, tmp)) != NULL) {
		if (tmp == pdev ||
		    pci_domain_nr(tmp->bus) != pci_domain_nr(pdev->bus) ||
		    pci_is_root_bus(tmp->bus))
			continue;

		if (tmp->bus->number >= pdev->bus->number &&
		    tmp->bus->number <= max_busnr) {
			pci_dev_put(tmp);
			decodes |= VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;
			break;
		}
	}

	return decodes;
}