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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {scalar_t__ bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  name; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct ipheth_device {int confirmed_pairing; int /*<<< orphan*/ * ctrl_buf; int /*<<< orphan*/  carrier_work; scalar_t__ bulk_out; scalar_t__ bulk_in; struct usb_interface* intf; struct net_device* net; struct usb_device* udev; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPHETH_ALT_INTFNUM ; 
 int /*<<< orphan*/  IPHETH_CTRL_BUF_SIZE ; 
 int /*<<< orphan*/  IPHETH_TX_TIMEOUT ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int ipheth_alloc_urbs (struct ipheth_device*) ; 
 int /*<<< orphan*/  ipheth_carrier_check_work ; 
 int /*<<< orphan*/  ipheth_free_urbs (struct ipheth_device*) ; 
 int ipheth_get_macaddr (struct ipheth_device*) ; 
 int /*<<< orphan*/  ipheth_netdev_ops ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipheth_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  ops ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_is_bulk_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_bulk_out (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct ipheth_device*) ; 

__attribute__((used)) static int ipheth_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct usb_host_interface *hintf;
	struct usb_endpoint_descriptor *endp;
	struct ipheth_device *dev;
	struct net_device *netdev;
	int i;
	int retval;

	netdev = alloc_etherdev(sizeof(struct ipheth_device));
	if (!netdev)
		return -ENOMEM;

	netdev->netdev_ops = &ipheth_netdev_ops;
	netdev->watchdog_timeo = IPHETH_TX_TIMEOUT;
	strcpy(netdev->name, "eth%d");

	dev = netdev_priv(netdev);
	dev->udev = udev;
	dev->net = netdev;
	dev->intf = intf;
	dev->confirmed_pairing = false;
	/* Set up endpoints */
	hintf = usb_altnum_to_altsetting(intf, IPHETH_ALT_INTFNUM);
	if (hintf == NULL) {
		retval = -ENODEV;
		dev_err(&intf->dev, "Unable to find alternate settings interface\n");
		goto err_endpoints;
	}

	for (i = 0; i < hintf->desc.bNumEndpoints; i++) {
		endp = &hintf->endpoint[i].desc;
		if (usb_endpoint_is_bulk_in(endp))
			dev->bulk_in = endp->bEndpointAddress;
		else if (usb_endpoint_is_bulk_out(endp))
			dev->bulk_out = endp->bEndpointAddress;
	}
	if (!(dev->bulk_in && dev->bulk_out)) {
		retval = -ENODEV;
		dev_err(&intf->dev, "Unable to find endpoints\n");
		goto err_endpoints;
	}

	dev->ctrl_buf = kmalloc(IPHETH_CTRL_BUF_SIZE, GFP_KERNEL);
	if (dev->ctrl_buf == NULL) {
		retval = -ENOMEM;
		goto err_alloc_ctrl_buf;
	}

	retval = ipheth_get_macaddr(dev);
	if (retval)
		goto err_get_macaddr;

	INIT_DELAYED_WORK(&dev->carrier_work, ipheth_carrier_check_work);

	retval = ipheth_alloc_urbs(dev);
	if (retval) {
		dev_err(&intf->dev, "error allocating urbs: %d\n", retval);
		goto err_alloc_urbs;
	}

	usb_set_intfdata(intf, dev);

	SET_NETDEV_DEV(netdev, &intf->dev);
	netdev->ethtool_ops = &ops;

	retval = register_netdev(netdev);
	if (retval) {
		dev_err(&intf->dev, "error registering netdev: %d\n", retval);
		retval = -EIO;
		goto err_register_netdev;
	}
	// carrier down and transmit queues stopped until packet from device
	netif_carrier_off(netdev);
	netif_tx_stop_all_queues(netdev);
	dev_info(&intf->dev, "Apple iPhone USB Ethernet device attached\n");
	return 0;

err_register_netdev:
	ipheth_free_urbs(dev);
err_alloc_urbs:
err_get_macaddr:
err_alloc_ctrl_buf:
	kfree(dev->ctrl_buf);
err_endpoints:
	free_netdev(netdev);
	return retval;
}