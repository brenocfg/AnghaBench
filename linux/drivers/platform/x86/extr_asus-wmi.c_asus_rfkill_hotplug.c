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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct pci_bus {int dummy; } ;
struct TYPE_4__ {scalar_t__ ops; } ;
struct TYPE_3__ {scalar_t__ rfkill; } ;
struct asus_wmi {int /*<<< orphan*/  hotplug_lock; TYPE_2__ hotplug_slot; TYPE_1__ wlan; int /*<<< orphan*/  wmi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int asus_wlan_rfkill_blocked (struct asus_wmi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_add_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_bus_assign_resources (struct pci_bus*) ; 
 scalar_t__ pci_bus_read_config_dword (struct pci_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_bus* pci_find_bus (int /*<<< orphan*/ ,int) ; 
 struct pci_dev* pci_get_slot (struct pci_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 struct pci_dev* pci_scan_single_device (struct pci_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_stop_and_remove_bus_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (scalar_t__,int) ; 

__attribute__((used)) static void asus_rfkill_hotplug(struct asus_wmi *asus)
{
	struct pci_dev *dev;
	struct pci_bus *bus;
	bool blocked;
	bool absent;
	u32 l;

	mutex_lock(&asus->wmi_lock);
	blocked = asus_wlan_rfkill_blocked(asus);
	mutex_unlock(&asus->wmi_lock);

	mutex_lock(&asus->hotplug_lock);
	pci_lock_rescan_remove();

	if (asus->wlan.rfkill)
		rfkill_set_sw_state(asus->wlan.rfkill, blocked);

	if (asus->hotplug_slot.ops) {
		bus = pci_find_bus(0, 1);
		if (!bus) {
			pr_warn("Unable to find PCI bus 1?\n");
			goto out_unlock;
		}

		if (pci_bus_read_config_dword(bus, 0, PCI_VENDOR_ID, &l)) {
			pr_err("Unable to read PCI config space?\n");
			goto out_unlock;
		}
		absent = (l == 0xffffffff);

		if (blocked != absent) {
			pr_warn("BIOS says wireless lan is %s, "
				"but the pci device is %s\n",
				blocked ? "blocked" : "unblocked",
				absent ? "absent" : "present");
			pr_warn("skipped wireless hotplug as probably "
				"inappropriate for this model\n");
			goto out_unlock;
		}

		if (!blocked) {
			dev = pci_get_slot(bus, 0);
			if (dev) {
				/* Device already present */
				pci_dev_put(dev);
				goto out_unlock;
			}
			dev = pci_scan_single_device(bus, 0);
			if (dev) {
				pci_bus_assign_resources(bus);
				pci_bus_add_device(dev);
			}
		} else {
			dev = pci_get_slot(bus, 0);
			if (dev) {
				pci_stop_and_remove_bus_device(dev);
				pci_dev_put(dev);
			}
		}
	}

out_unlock:
	pci_unlock_rescan_remove();
	mutex_unlock(&asus->hotplug_lock);
}