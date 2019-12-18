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
struct pci_slot {struct hotplug_slot* hotplug; } ;
struct hotplug_slot {TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ get_attention_status; scalar_t__ set_attention_status; } ;

/* Variables and functions */

__attribute__((used)) static bool has_attention_file(struct pci_slot *pci_slot)
{
	struct hotplug_slot *slot = pci_slot->hotplug;

	if ((!slot) || (!slot->ops))
		return false;
	if ((slot->ops->set_attention_status) ||
	    (slot->ops->get_attention_status))
		return true;
	return false;
}