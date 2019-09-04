#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_controller {int dummy; } ;
struct pci_bus {TYPE_3__* legacy_io; TYPE_2__* legacy_mem; struct pci_controller* sysdata; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;
struct TYPE_8__ {char* name; } ;
struct TYPE_7__ {int size; TYPE_4__ attr; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_6__ {int size; TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  has_sparse (struct pci_controller*,int) ; 
 int pci_mmap_mem ; 

void pci_adjust_legacy_attr(struct pci_bus *bus, enum pci_mmap_state mmap_type)
{
	struct pci_controller *hose = bus->sysdata;

	if (!has_sparse(hose, mmap_type))
		return;

	if (mmap_type == pci_mmap_mem) {
		bus->legacy_mem->attr.name = "legacy_mem_sparse";
		bus->legacy_mem->size <<= 5;
	} else {
		bus->legacy_io->attr.name = "legacy_io_sparse";
		bus->legacy_io->size <<= 5;
	}
	return;
}