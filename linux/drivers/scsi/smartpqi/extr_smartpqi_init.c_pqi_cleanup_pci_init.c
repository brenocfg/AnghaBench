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
struct pqi_ctrl_info {int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  iomem_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pqi_cleanup_pci_init(struct pqi_ctrl_info *ctrl_info)
{
	iounmap(ctrl_info->iomem_base);
	pci_release_regions(ctrl_info->pci_dev);
	if (pci_is_enabled(ctrl_info->pci_dev))
		pci_disable_device(ctrl_info->pci_dev);
	pci_set_drvdata(ctrl_info->pci_dev, NULL);
}