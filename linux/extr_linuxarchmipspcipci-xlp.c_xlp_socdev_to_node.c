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
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* self; } ;
struct TYPE_3__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_xlp9xx () ; 

int xlp_socdev_to_node(const struct pci_dev *lnkdev)
{
	if (cpu_is_xlp9xx())
		return PCI_FUNC(lnkdev->bus->self->devfn);
	else
		return PCI_SLOT(lnkdev->devfn) / 8;
}