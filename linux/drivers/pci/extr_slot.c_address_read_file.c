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
struct pci_slot {int number; TYPE_1__* bus; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int pci_domain_nr (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,...) ; 

__attribute__((used)) static ssize_t address_read_file(struct pci_slot *slot, char *buf)
{
	if (slot->number == 0xff)
		return sprintf(buf, "%04x:%02x\n",
				pci_domain_nr(slot->bus),
				slot->bus->number);
	else
		return sprintf(buf, "%04x:%02x:%02x\n",
				pci_domain_nr(slot->bus),
				slot->bus->number,
				slot->number);
}