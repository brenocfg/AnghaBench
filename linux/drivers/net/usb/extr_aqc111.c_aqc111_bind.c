#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct usbnet {int can_dma_sg; TYPE_3__* net; int /*<<< orphan*/  udev; int /*<<< orphan*/  rx_urb_size; struct aqc111_data* driver_priv; } ;
struct usb_interface {int dummy; } ;
struct usb_device {int speed; TYPE_2__* actconfig; } ;
struct aqc111_data {int /*<<< orphan*/  advertised_speed; int /*<<< orphan*/  autoneg; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_7__ {int needed_headroom; int needed_tailroom; int max_mtu; int /*<<< orphan*/  vlan_features; int /*<<< orphan*/  features; int /*<<< orphan*/  hw_features; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {int bConfigurationValue; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_SUPPORT_FEATURE ; 
 int /*<<< orphan*/  AQ_SUPPORT_HW_FEATURE ; 
 int /*<<< orphan*/  AQ_SUPPORT_VLAN_FEATURE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_5000 ; 
 int /*<<< orphan*/  URB_SIZE ; 
 int USB_SPEED_SUPER ; 
 int /*<<< orphan*/  aqc111_ethtool_ops ; 
 int /*<<< orphan*/  aqc111_netdev_ops ; 
 int /*<<< orphan*/  aqc111_read_fw_version (struct usbnet*,struct aqc111_data*) ; 
 int aqc111_read_perm_mac (struct usbnet*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct aqc111_data*) ; 
 struct aqc111_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  netif_set_gso_max_size (TYPE_3__*,int) ; 
 scalar_t__ usb_device_no_sg_constraint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_driver_set_configuration (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_reset_configuration (int /*<<< orphan*/ ) ; 
 int usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int aqc111_bind(struct usbnet *dev, struct usb_interface *intf)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	enum usb_device_speed usb_speed = udev->speed;
	struct aqc111_data *aqc111_data;
	int ret;

	/* Check if vendor configuration */
	if (udev->actconfig->desc.bConfigurationValue != 1) {
		usb_driver_set_configuration(udev, 1);
		return -ENODEV;
	}

	usb_reset_configuration(dev->udev);

	ret = usbnet_get_endpoints(dev, intf);
	if (ret < 0) {
		netdev_dbg(dev->net, "usbnet_get_endpoints failed");
		return ret;
	}

	aqc111_data = kzalloc(sizeof(*aqc111_data), GFP_KERNEL);
	if (!aqc111_data)
		return -ENOMEM;

	/* store aqc111_data pointer in device data field */
	dev->driver_priv = aqc111_data;

	/* Init the MAC address */
	ret = aqc111_read_perm_mac(dev);
	if (ret)
		goto out;

	ether_addr_copy(dev->net->dev_addr, dev->net->perm_addr);

	/* Set Rx urb size */
	dev->rx_urb_size = URB_SIZE;

	/* Set TX needed headroom & tailroom */
	dev->net->needed_headroom += sizeof(u64);
	dev->net->needed_tailroom += sizeof(u64);

	dev->net->max_mtu = 16334;

	dev->net->netdev_ops = &aqc111_netdev_ops;
	dev->net->ethtool_ops = &aqc111_ethtool_ops;

	if (usb_device_no_sg_constraint(dev->udev))
		dev->can_dma_sg = 1;

	dev->net->hw_features |= AQ_SUPPORT_HW_FEATURE;
	dev->net->features |= AQ_SUPPORT_FEATURE;
	dev->net->vlan_features |= AQ_SUPPORT_VLAN_FEATURE;

	netif_set_gso_max_size(dev->net, 65535);

	aqc111_read_fw_version(dev, aqc111_data);
	aqc111_data->autoneg = AUTONEG_ENABLE;
	aqc111_data->advertised_speed = (usb_speed == USB_SPEED_SUPER) ?
					 SPEED_5000 : SPEED_1000;

	return 0;

out:
	kfree(aqc111_data);
	return ret;
}