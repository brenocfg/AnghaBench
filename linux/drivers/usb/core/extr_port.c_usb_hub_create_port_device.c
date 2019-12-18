#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * driver; int /*<<< orphan*/ * type; int /*<<< orphan*/  groups; int /*<<< orphan*/  parent; } ;
struct usb_port {int portnum; int usb3_lpm_u1_permit; int usb3_lpm_u2_permit; int is_superspeed; struct usb_port* req; TYPE_1__ dev; int /*<<< orphan*/  status_lock; } ;
struct usb_hub {struct usb_device* hdev; int /*<<< orphan*/  intfdev; int /*<<< orphan*/  power_bits; struct usb_port** ports; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PM_QOS_FLAGS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PM_QOS_FLAG_NO_POWER_OFF ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int dev_pm_qos_add_request (TYPE_1__*,struct usb_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dev_pm_qos_expose_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dev_pm_qos_remove_request (struct usb_port*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  device_enable_async_suspend (TYPE_1__*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  find_and_link_peer (struct usb_hub*,int) ; 
 int /*<<< orphan*/  hub_is_port_power_switchable (struct usb_hub*) ; 
 scalar_t__ hub_is_superspeed (struct usb_device*) ; 
 int /*<<< orphan*/  kfree (struct usb_port*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  port_dev_group ; 
 int /*<<< orphan*/  port_dev_usb3_group ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_port_device_type ; 
 int /*<<< orphan*/  usb_port_driver ; 

int usb_hub_create_port_device(struct usb_hub *hub, int port1)
{
	struct usb_port *port_dev;
	struct usb_device *hdev = hub->hdev;
	int retval;

	port_dev = kzalloc(sizeof(*port_dev), GFP_KERNEL);
	if (!port_dev)
		return -ENOMEM;

	port_dev->req = kzalloc(sizeof(*(port_dev->req)), GFP_KERNEL);
	if (!port_dev->req) {
		kfree(port_dev);
		return -ENOMEM;
	}

	hub->ports[port1 - 1] = port_dev;
	port_dev->portnum = port1;
	set_bit(port1, hub->power_bits);
	port_dev->dev.parent = hub->intfdev;
	if (hub_is_superspeed(hdev)) {
		port_dev->usb3_lpm_u1_permit = 1;
		port_dev->usb3_lpm_u2_permit = 1;
		port_dev->dev.groups = port_dev_usb3_group;
	} else
		port_dev->dev.groups = port_dev_group;
	port_dev->dev.type = &usb_port_device_type;
	port_dev->dev.driver = &usb_port_driver;
	if (hub_is_superspeed(hub->hdev))
		port_dev->is_superspeed = 1;
	dev_set_name(&port_dev->dev, "%s-port%d", dev_name(&hub->hdev->dev),
			port1);
	mutex_init(&port_dev->status_lock);
	retval = device_register(&port_dev->dev);
	if (retval) {
		put_device(&port_dev->dev);
		return retval;
	}

	/* Set default policy of port-poweroff disabled. */
	retval = dev_pm_qos_add_request(&port_dev->dev, port_dev->req,
			DEV_PM_QOS_FLAGS, PM_QOS_FLAG_NO_POWER_OFF);
	if (retval < 0) {
		device_unregister(&port_dev->dev);
		return retval;
	}

	find_and_link_peer(hub, port1);

	/*
	 * Enable runtime pm and hold a refernce that hub_configure()
	 * will drop once the PM_QOS_NO_POWER_OFF flag state has been set
	 * and the hub has been fully registered (hdev->maxchild set).
	 */
	pm_runtime_set_active(&port_dev->dev);
	pm_runtime_get_noresume(&port_dev->dev);
	pm_runtime_enable(&port_dev->dev);
	device_enable_async_suspend(&port_dev->dev);

	/*
	 * Keep hidden the ability to enable port-poweroff if the hub
	 * does not support power switching.
	 */
	if (!hub_is_port_power_switchable(hub))
		return 0;

	/* Attempt to let userspace take over the policy. */
	retval = dev_pm_qos_expose_flags(&port_dev->dev,
			PM_QOS_FLAG_NO_POWER_OFF);
	if (retval < 0) {
		dev_warn(&port_dev->dev, "failed to expose pm_qos_no_poweroff\n");
		return 0;
	}

	/* Userspace owns the policy, drop the kernel 'no_poweroff' request. */
	retval = dev_pm_qos_remove_request(port_dev->req);
	if (retval >= 0) {
		kfree(port_dev->req);
		port_dev->req = NULL;
	}
	return 0;
}