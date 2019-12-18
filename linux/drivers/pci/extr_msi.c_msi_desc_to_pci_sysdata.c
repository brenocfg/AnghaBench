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
struct pci_dev {TYPE_1__* bus; } ;
struct msi_desc {int dummy; } ;
struct TYPE_2__ {void* sysdata; } ;

/* Variables and functions */
 struct pci_dev* msi_desc_to_pci_dev (struct msi_desc*) ; 

void *msi_desc_to_pci_sysdata(struct msi_desc *desc)
{
	struct pci_dev *dev = msi_desc_to_pci_dev(desc);

	return dev->bus->sysdata;
}