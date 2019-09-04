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
struct pci_dev {scalar_t__ devfn; int broken_parity_status; TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVFN (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void n2100_fixup_r8169(struct pci_dev *dev)
{
	if (dev->bus->number == 0 &&
	    (dev->devfn == PCI_DEVFN(1, 0) ||
	     dev->devfn == PCI_DEVFN(2, 0)))
		dev->broken_parity_status = 1;
}