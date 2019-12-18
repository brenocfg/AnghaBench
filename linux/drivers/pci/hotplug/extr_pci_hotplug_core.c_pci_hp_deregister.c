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
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_hp_del (struct hotplug_slot*) ; 
 int /*<<< orphan*/  pci_hp_destroy (struct hotplug_slot*) ; 

void pci_hp_deregister(struct hotplug_slot *slot)
{
	pci_hp_del(slot);
	pci_hp_destroy(slot);
}