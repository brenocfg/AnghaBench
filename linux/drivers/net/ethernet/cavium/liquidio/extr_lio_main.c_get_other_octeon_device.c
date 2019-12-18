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
struct octeon_device {TYPE_2__* pci_dev; scalar_t__ octeon_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_3__ {int number; } ;

/* Variables and functions */
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 struct octeon_device* lio_get_device (scalar_t__) ; 

__attribute__((used)) static struct octeon_device *get_other_octeon_device(struct octeon_device *oct)
{
	struct octeon_device *other_oct;

	other_oct = lio_get_device(oct->octeon_id + 1);

	if (other_oct && other_oct->pci_dev) {
		int oct_busnum, other_oct_busnum;

		oct_busnum = oct->pci_dev->bus->number;
		other_oct_busnum = other_oct->pci_dev->bus->number;

		if (oct_busnum == other_oct_busnum) {
			int oct_slot, other_oct_slot;

			oct_slot = PCI_SLOT(oct->pci_dev->devfn);
			other_oct_slot = PCI_SLOT(other_oct->pci_dev->devfn);

			if (oct_slot == other_oct_slot)
				return other_oct;
		}
	}

	return NULL;
}