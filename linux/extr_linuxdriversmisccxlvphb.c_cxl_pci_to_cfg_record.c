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
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 unsigned int cxl_pcie_cfg_record (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int cxl_pci_to_cfg_record(struct pci_dev *dev)
{
	return cxl_pcie_cfg_record(dev->bus->number, dev->devfn);
}