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
typedef  scalar_t__ uint8_t ;
struct pnv_php_slot {int /*<<< orphan*/  pdev; TYPE_1__* dn; int /*<<< orphan*/  id; } ;
struct opal_msg {int /*<<< orphan*/ * params; } ;
struct hotplug_slot {int dummy; } ;
struct TYPE_2__ {scalar_t__ phandle; } ;

/* Variables and functions */
 int ENOMSG ; 
 scalar_t__ OPAL_PCI_SLOT_OFFLINE ; 
 scalar_t__ OPAL_PCI_SLOT_POWER_OFF ; 
 scalar_t__ OPAL_PCI_SLOT_POWER_ON ; 
 scalar_t__ OPAL_SUCCESS ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_warn (int /*<<< orphan*/ ,char*,int,char*,...) ; 
 int pnv_pci_set_power_state (int /*<<< orphan*/ ,scalar_t__,struct opal_msg*) ; 
 int pnv_php_add_devtree (struct pnv_php_slot*) ; 
 int /*<<< orphan*/  pnv_php_rmv_devtree (struct pnv_php_slot*) ; 
 struct pnv_php_slot* to_pnv_php_slot (struct hotplug_slot*) ; 

int pnv_php_set_slot_power_state(struct hotplug_slot *slot,
				 uint8_t state)
{
	struct pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	struct opal_msg msg;
	int ret;

	ret = pnv_pci_set_power_state(php_slot->id, state, &msg);
	if (ret > 0) {
		if (be64_to_cpu(msg.params[1]) != php_slot->dn->phandle	||
		    be64_to_cpu(msg.params[2]) != state			||
		    be64_to_cpu(msg.params[3]) != OPAL_SUCCESS) {
			pci_warn(php_slot->pdev, "Wrong msg (%lld, %lld, %lld)\n",
				 be64_to_cpu(msg.params[1]),
				 be64_to_cpu(msg.params[2]),
				 be64_to_cpu(msg.params[3]));
			return -ENOMSG;
		}
	} else if (ret < 0) {
		pci_warn(php_slot->pdev, "Error %d powering %s\n",
			 ret, (state == OPAL_PCI_SLOT_POWER_ON) ? "on" : "off");
		return ret;
	}

	if (state == OPAL_PCI_SLOT_POWER_OFF || state == OPAL_PCI_SLOT_OFFLINE)
		pnv_php_rmv_devtree(php_slot);
	else
		ret = pnv_php_add_devtree(php_slot);

	return ret;
}