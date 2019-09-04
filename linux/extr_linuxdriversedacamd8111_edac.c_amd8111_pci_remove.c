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
struct pci_dev {scalar_t__ device; } ;
struct amd8111_pci_info {TYPE_1__* dev; int /*<<< orphan*/  (* exit ) (struct amd8111_pci_info*) ;TYPE_2__* edac_dev; scalar_t__ err_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ device; } ;

/* Variables and functions */
 struct amd8111_pci_info* amd8111_pcis ; 
 int /*<<< orphan*/  edac_pci_del_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_pci_free_ctl_info (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct amd8111_pci_info*) ; 

__attribute__((used)) static void amd8111_pci_remove(struct pci_dev *dev)
{
	struct amd8111_pci_info *pci_info;

	for (pci_info = amd8111_pcis; pci_info->err_dev; pci_info++)
		if (pci_info->dev->device == dev->device)
			break;

	if (!pci_info->err_dev)	/* should never happen */
		return;

	if (pci_info->edac_dev) {
		edac_pci_del_device(pci_info->edac_dev->dev);
		edac_pci_free_ctl_info(pci_info->edac_dev);
	}

	if (pci_info->exit)
		pci_info->exit(pci_info);

	pci_dev_put(pci_info->dev);
}