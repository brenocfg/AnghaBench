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
struct pcie_device {scalar_t__ service; TYPE_1__* port; } ;
struct controller {int /*<<< orphan*/  hotplug_slot; } ;
struct TYPE_2__ {int /*<<< orphan*/  subordinate; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ PCIE_PORT_SERVICE_HP ; 
 int /*<<< orphan*/  cleanup_slot (struct controller*) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int) ; 
 int /*<<< orphan*/  ctrl_warn (struct controller*,char*) ; 
 int init_slot (struct controller*) ; 
 int /*<<< orphan*/  pci_err (TYPE_1__*,char*) ; 
 int pci_hp_add (int /*<<< orphan*/ *) ; 
 struct controller* pcie_init (struct pcie_device*) ; 
 int pcie_init_notification (struct controller*) ; 
 int /*<<< orphan*/  pcie_shutdown_notification (struct controller*) ; 
 int /*<<< orphan*/  pciehp_check_presence (struct controller*) ; 
 int /*<<< orphan*/  pciehp_release_ctrl (struct controller*) ; 
 int /*<<< orphan*/  set_service_data (struct pcie_device*,struct controller*) ; 

__attribute__((used)) static int pciehp_probe(struct pcie_device *dev)
{
	int rc;
	struct controller *ctrl;

	/* If this is not a "hotplug" service, we have no business here. */
	if (dev->service != PCIE_PORT_SERVICE_HP)
		return -ENODEV;

	if (!dev->port->subordinate) {
		/* Can happen if we run out of bus numbers during probe */
		pci_err(dev->port,
			"Hotplug bridge without secondary bus, ignoring\n");
		return -ENODEV;
	}

	ctrl = pcie_init(dev);
	if (!ctrl) {
		pci_err(dev->port, "Controller initialization failed\n");
		return -ENODEV;
	}
	set_service_data(dev, ctrl);

	/* Setup the slot information structures */
	rc = init_slot(ctrl);
	if (rc) {
		if (rc == -EBUSY)
			ctrl_warn(ctrl, "Slot already registered by another hotplug driver\n");
		else
			ctrl_err(ctrl, "Slot initialization failed (%d)\n", rc);
		goto err_out_release_ctlr;
	}

	/* Enable events after we have setup the data structures */
	rc = pcie_init_notification(ctrl);
	if (rc) {
		ctrl_err(ctrl, "Notification initialization failed (%d)\n", rc);
		goto err_out_free_ctrl_slot;
	}

	/* Publish to user space */
	rc = pci_hp_add(&ctrl->hotplug_slot);
	if (rc) {
		ctrl_err(ctrl, "Publication to user space failed (%d)\n", rc);
		goto err_out_shutdown_notification;
	}

	pciehp_check_presence(ctrl);

	return 0;

err_out_shutdown_notification:
	pcie_shutdown_notification(ctrl);
err_out_free_ctrl_slot:
	cleanup_slot(ctrl);
err_out_release_ctlr:
	pciehp_release_ctrl(ctrl);
	return -ENODEV;
}