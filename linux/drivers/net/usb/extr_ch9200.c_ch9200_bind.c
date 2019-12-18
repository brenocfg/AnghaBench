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
struct TYPE_4__ {int reg_num_mask; int phy_id_mask; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; TYPE_1__* dev; } ;
struct usbnet {int rx_urb_size; TYPE_1__* net; TYPE_2__ mii; scalar_t__ hard_mtu; } ;
struct usb_interface {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; scalar_t__ hard_header_len; scalar_t__ mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_TIMEOUT_MS ; 
 int MAC_REG_CTRL ; 
 int MAC_REG_FIFO_DEPTH ; 
 int MAC_REG_FLOW_CONTROL ; 
 int MAC_REG_PAUSE ; 
 int MAC_REG_THRESHOLD ; 
 int /*<<< orphan*/  REQUEST_WRITE ; 
 int /*<<< orphan*/  ch9200_mdio_read ; 
 int /*<<< orphan*/  ch9200_mdio_write ; 
 int control_write (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int get_mac_address (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_nway_restart (TYPE_2__*) ; 
 int usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int ch9200_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int retval = 0;
	unsigned char data[2];

	retval = usbnet_get_endpoints(dev, intf);
	if (retval)
		return retval;

	dev->mii.dev = dev->net;
	dev->mii.mdio_read = ch9200_mdio_read;
	dev->mii.mdio_write = ch9200_mdio_write;
	dev->mii.reg_num_mask = 0x1f;

	dev->mii.phy_id_mask = 0x1f;

	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;
	dev->rx_urb_size = 24 * 64 + 16;
	mii_nway_restart(&dev->mii);

	data[0] = 0x01;
	data[1] = 0x0F;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_THRESHOLD, data,
			       0x02, CONTROL_TIMEOUT_MS);

	data[0] = 0xA0;
	data[1] = 0x90;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_FIFO_DEPTH, data,
			       0x02, CONTROL_TIMEOUT_MS);

	data[0] = 0x30;
	data[1] = 0x00;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_PAUSE, data,
			       0x02, CONTROL_TIMEOUT_MS);

	data[0] = 0x17;
	data[1] = 0xD8;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_FLOW_CONTROL,
			       data, 0x02, CONTROL_TIMEOUT_MS);

	/* Undocumented register */
	data[0] = 0x01;
	data[1] = 0x00;
	retval = control_write(dev, REQUEST_WRITE, 0, 254, data, 0x02,
			       CONTROL_TIMEOUT_MS);

	data[0] = 0x5F;
	data[1] = 0x0D;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_CTRL, data, 0x02,
			       CONTROL_TIMEOUT_MS);

	retval = get_mac_address(dev, dev->net->dev_addr);

	return retval;
}