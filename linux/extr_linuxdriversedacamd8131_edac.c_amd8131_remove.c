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
struct pci_dev {scalar_t__ devfn; } ;
struct amd8131_dev_info {scalar_t__ inst; scalar_t__ devfn; int /*<<< orphan*/  dev; TYPE_1__* edac_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* exit ) (struct amd8131_dev_info*) ;struct amd8131_dev_info* devices; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ NO_BRIDGE ; 
 TYPE_2__ amd8131_chipset ; 
 int /*<<< orphan*/  edac_pci_del_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_pci_free_ctl_info (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct amd8131_dev_info*) ; 

__attribute__((used)) static void amd8131_remove(struct pci_dev *dev)
{
	struct amd8131_dev_info *dev_info;

	for (dev_info = amd8131_chipset.devices; dev_info->inst != NO_BRIDGE;
		dev_info++)
		if (dev_info->devfn == dev->devfn)
			break;

	if (dev_info->inst == NO_BRIDGE) /* should never happen */
		return;

	if (dev_info->edac_dev) {
		edac_pci_del_device(dev_info->edac_dev->dev);
		edac_pci_free_ctl_info(dev_info->edac_dev);
	}

	if (amd8131_chipset.exit)
		amd8131_chipset.exit(dev_info);

	pci_dev_put(dev_info->dev);
}