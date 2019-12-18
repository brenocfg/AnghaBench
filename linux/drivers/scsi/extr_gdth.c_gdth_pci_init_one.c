#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
typedef  int /*<<< orphan*/  gdth_pcistr ;
struct TYPE_6__ {void* dpmem; int /*<<< orphan*/  irq; struct pci_dev* pdev; void* io; } ;
typedef  TYPE_2__ gdth_pci_str ;
typedef  int /*<<< orphan*/  gdth_ha_str ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 scalar_t__ MAXHA ; 
 scalar_t__ PCI_DEVICE_ID_VORTEX_GDT6000B ; 
 scalar_t__ PCI_DEVICE_ID_VORTEX_GDT6x17RP ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_ID_VORTEX ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRACE2 (char*) ; 
 scalar_t__ gdth_ctr_count ; 
 int gdth_pci_probe_one (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  gdth_search_vortex (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int pci_enable_device (struct pci_dev*) ; 
 unsigned long pci_resource_flags (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static int gdth_pci_init_one(struct pci_dev *pdev,
			     const struct pci_device_id *ent)
{
	u16 vendor = pdev->vendor;
	u16 device = pdev->device;
	unsigned long base0, base1, base2;
	int rc;
	gdth_pci_str gdth_pcistr;
	gdth_ha_str *ha = NULL;
    
	TRACE(("gdth_search_dev() cnt %d vendor %x device %x\n",
	       gdth_ctr_count, vendor, device));

	memset(&gdth_pcistr, 0, sizeof(gdth_pcistr));

	if (vendor == PCI_VENDOR_ID_VORTEX && !gdth_search_vortex(device))
		return -ENODEV;

	rc = pci_enable_device(pdev);
	if (rc)
		return rc;

	if (gdth_ctr_count >= MAXHA)
		return -EBUSY;

        /* GDT PCI controller found, resources are already in pdev */
	gdth_pcistr.pdev = pdev;
        base0 = pci_resource_flags(pdev, 0);
        base1 = pci_resource_flags(pdev, 1);
        base2 = pci_resource_flags(pdev, 2);
        if (device <= PCI_DEVICE_ID_VORTEX_GDT6000B ||   /* GDT6000/B */
            device >= PCI_DEVICE_ID_VORTEX_GDT6x17RP) {  /* MPR */
            if (!(base0 & IORESOURCE_MEM)) 
		return -ENODEV;
	    gdth_pcistr.dpmem = pci_resource_start(pdev, 0);
        } else {                                  /* GDT6110, GDT6120, .. */
            if (!(base0 & IORESOURCE_MEM) ||
                !(base2 & IORESOURCE_MEM) ||
                !(base1 & IORESOURCE_IO)) 
		return -ENODEV;
	    gdth_pcistr.dpmem = pci_resource_start(pdev, 2);
	    gdth_pcistr.io    = pci_resource_start(pdev, 1);
        }
        TRACE2(("Controller found at %d/%d, irq %d, dpmem 0x%lx\n",
		gdth_pcistr.pdev->bus->number,
		PCI_SLOT(gdth_pcistr.pdev->devfn),
		gdth_pcistr.irq,
		gdth_pcistr.dpmem));

	rc = gdth_pci_probe_one(&gdth_pcistr, &ha);
	if (rc)
		return rc;

	return 0;
}