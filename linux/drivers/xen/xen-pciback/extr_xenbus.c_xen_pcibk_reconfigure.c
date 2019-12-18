#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xen_pcibk_device {int /*<<< orphan*/  dev_lock; TYPE_1__* xdev; } ;
typedef  int /*<<< orphan*/  state_str ;
typedef  int /*<<< orphan*/  dev_str ;
struct TYPE_3__ {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  XBT_NIL ; 
#define  XenbusStateClosing 129 
 int /*<<< orphan*/  XenbusStateInitialised ; 
#define  XenbusStateInitialising 128 
 int /*<<< orphan*/  XenbusStateReconfigured ; 
 scalar_t__ XenbusStateReconfiguring ; 
 int /*<<< orphan*/  XenbusStateUnknown ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int xen_pcibk_export_device (struct xen_pcibk_device*,int,int,int,int,int) ; 
 int /*<<< orphan*/  xen_pcibk_publish_pci_root ; 
 int xen_pcibk_publish_pci_roots (struct xen_pcibk_device*,int /*<<< orphan*/ ) ; 
 int xen_pcibk_remove_device (struct xen_pcibk_device*,int,int,int,int) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (TYPE_1__*,int,char*,...) ; 
 int xenbus_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xenbus_read_driver_state (int /*<<< orphan*/ ) ; 
 unsigned int xenbus_read_unsigned (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int xenbus_scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int*,...) ; 
 int xenbus_switch_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xen_pcibk_reconfigure(struct xen_pcibk_device *pdev)
{
	int err = 0;
	int num_devs;
	int domain, bus, slot, func;
	unsigned int substate;
	int i, len;
	char state_str[64];
	char dev_str[64];


	dev_dbg(&pdev->xdev->dev, "Reconfiguring device ...\n");

	mutex_lock(&pdev->dev_lock);
	/* Make sure we only reconfigure once */
	if (xenbus_read_driver_state(pdev->xdev->nodename) !=
	    XenbusStateReconfiguring)
		goto out;

	err = xenbus_scanf(XBT_NIL, pdev->xdev->nodename, "num_devs", "%d",
			   &num_devs);
	if (err != 1) {
		if (err >= 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading number of devices");
		goto out;
	}

	for (i = 0; i < num_devs; i++) {
		len = snprintf(state_str, sizeof(state_str), "state-%d", i);
		if (unlikely(len >= (sizeof(state_str) - 1))) {
			err = -ENOMEM;
			xenbus_dev_fatal(pdev->xdev, err,
					 "String overflow while reading "
					 "configuration");
			goto out;
		}
		substate = xenbus_read_unsigned(pdev->xdev->nodename, state_str,
						XenbusStateUnknown);

		switch (substate) {
		case XenbusStateInitialising:
			dev_dbg(&pdev->xdev->dev, "Attaching dev-%d ...\n", i);

			len = snprintf(dev_str, sizeof(dev_str), "dev-%d", i);
			if (unlikely(len >= (sizeof(dev_str) - 1))) {
				err = -ENOMEM;
				xenbus_dev_fatal(pdev->xdev, err,
						 "String overflow while "
						 "reading configuration");
				goto out;
			}
			err = xenbus_scanf(XBT_NIL, pdev->xdev->nodename,
					   dev_str, "%x:%x:%x.%x",
					   &domain, &bus, &slot, &func);
			if (err < 0) {
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error reading device "
						 "configuration");
				goto out;
			}
			if (err != 4) {
				err = -EINVAL;
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error parsing pci device "
						 "configuration");
				goto out;
			}

			err = xen_pcibk_export_device(pdev, domain, bus, slot,
						    func, i);
			if (err)
				goto out;

			/* Publish pci roots. */
			err = xen_pcibk_publish_pci_roots(pdev,
						xen_pcibk_publish_pci_root);
			if (err) {
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error while publish PCI root"
						 "buses for frontend");
				goto out;
			}

			err = xenbus_printf(XBT_NIL, pdev->xdev->nodename,
					    state_str, "%d",
					    XenbusStateInitialised);
			if (err) {
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error switching substate of "
						 "dev-%d\n", i);
				goto out;
			}
			break;

		case XenbusStateClosing:
			dev_dbg(&pdev->xdev->dev, "Detaching dev-%d ...\n", i);

			len = snprintf(dev_str, sizeof(dev_str), "vdev-%d", i);
			if (unlikely(len >= (sizeof(dev_str) - 1))) {
				err = -ENOMEM;
				xenbus_dev_fatal(pdev->xdev, err,
						 "String overflow while "
						 "reading configuration");
				goto out;
			}
			err = xenbus_scanf(XBT_NIL, pdev->xdev->nodename,
					   dev_str, "%x:%x:%x.%x",
					   &domain, &bus, &slot, &func);
			if (err < 0) {
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error reading device "
						 "configuration");
				goto out;
			}
			if (err != 4) {
				err = -EINVAL;
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error parsing pci device "
						 "configuration");
				goto out;
			}

			err = xen_pcibk_remove_device(pdev, domain, bus, slot,
						    func);
			if (err)
				goto out;

			/* TODO: If at some point we implement support for pci
			 * root hot-remove on pcifront side, we'll need to
			 * remove unnecessary xenstore nodes of pci roots here.
			 */

			break;

		default:
			break;
		}
	}

	err = xenbus_switch_state(pdev->xdev, XenbusStateReconfigured);
	if (err) {
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error switching to reconfigured state!");
		goto out;
	}

out:
	mutex_unlock(&pdev->dev_lock);
	return 0;
}