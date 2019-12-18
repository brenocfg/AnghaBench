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
struct rvu {struct pci_dev* pdev; } ;
struct pci_dev {int revision; scalar_t__ subsystem_device; } ;

/* Variables and functions */
 scalar_t__ PCI_SUBSYS_DEVID_96XX ; 

__attribute__((used)) static inline bool is_rvu_9xxx_A0(struct rvu *rvu)
{
	struct pci_dev *pdev = rvu->pdev;

	return (pdev->revision == 0x00) &&
		(pdev->subsystem_device == PCI_SUBSYS_DEVID_96XX);
}