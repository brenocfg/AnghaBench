#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {int hard_mtu; TYPE_5__* net; TYPE_4__* udev; TYPE_2__* driver_info; int /*<<< orphan*/  data; } ;
struct usb_interface_descriptor {scalar_t__ bInterfaceNumber; } ;
struct usb_interface {int /*<<< orphan*/  dev; TYPE_1__* cur_altsetting; } ;
struct usb_driver {int dummy; } ;
struct usb_cdc_union_desc {scalar_t__ bMasterInterface0; int /*<<< orphan*/  bSlaveInterface0; } ;
struct usb_cdc_parsed_header {struct usb_cdc_ether_desc* usb_cdc_ether_desc; struct usb_cdc_union_desc* usb_cdc_union_desc; } ;
struct usb_cdc_ether_desc {int /*<<< orphan*/  iMACAddress; scalar_t__ wMaxSegmentSize; } ;
struct qmi_wwan_state {struct usb_interface* data; struct usb_interface* control; } ;
struct TYPE_10__ {int* dev_addr; int /*<<< orphan*/ ** sysfs_groups; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_8__ {scalar_t__ bcdUSB; } ;
struct TYPE_9__ {TYPE_3__ descriptor; } ;
struct TYPE_7__ {int data; } ;
struct TYPE_6__ {int extralen; struct usb_interface_descriptor desc; int /*<<< orphan*/ * extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int QMI_WWAN_QUIRK_DTR ; 
 int /*<<< orphan*/  buggy_fw_addr ; 
 int /*<<< orphan*/  cdc_parse_cdc_header (struct usb_cdc_parsed_header*,struct usb_interface*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  default_modem_addr ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct usb_driver* driver_of (struct usb_interface*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_5__*) ; 
 scalar_t__ ether_addr_equal (int*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 
 scalar_t__ possibly_iphdr (int*) ; 
 int /*<<< orphan*/  qmi_wwan_change_dtr (struct usbnet*,int) ; 
 int /*<<< orphan*/  qmi_wwan_manage_power (struct usbnet*,int) ; 
 int /*<<< orphan*/  qmi_wwan_netdev_ops ; 
 int qmi_wwan_register_subdriver (struct usbnet*) ; 
 int /*<<< orphan*/  qmi_wwan_sysfs_attr_group ; 
 int usb_driver_claim_interface (struct usb_driver*,struct usb_interface*,struct usbnet*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (struct usb_driver*,struct usb_interface*) ; 
 struct usb_interface* usb_ifnum_to_if (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbnet_get_ethernet_addr (struct usbnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qmi_wwan_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int status = -1;
	u8 *buf = intf->cur_altsetting->extra;
	int len = intf->cur_altsetting->extralen;
	struct usb_interface_descriptor *desc = &intf->cur_altsetting->desc;
	struct usb_cdc_union_desc *cdc_union;
	struct usb_cdc_ether_desc *cdc_ether;
	struct usb_driver *driver = driver_of(intf);
	struct qmi_wwan_state *info = (void *)&dev->data;
	struct usb_cdc_parsed_header hdr;

	BUILD_BUG_ON((sizeof(((struct usbnet *)0)->data) <
		      sizeof(struct qmi_wwan_state)));

	/* set up initial state */
	info->control = intf;
	info->data = intf;

	/* and a number of CDC descriptors */
	cdc_parse_cdc_header(&hdr, intf, buf, len);
	cdc_union = hdr.usb_cdc_union_desc;
	cdc_ether = hdr.usb_cdc_ether_desc;

	/* Use separate control and data interfaces if we found a CDC Union */
	if (cdc_union) {
		info->data = usb_ifnum_to_if(dev->udev,
					     cdc_union->bSlaveInterface0);
		if (desc->bInterfaceNumber != cdc_union->bMasterInterface0 ||
		    !info->data) {
			dev_err(&intf->dev,
				"bogus CDC Union: master=%u, slave=%u\n",
				cdc_union->bMasterInterface0,
				cdc_union->bSlaveInterface0);

			/* ignore and continue... */
			cdc_union = NULL;
			info->data = intf;
		}
	}

	/* errors aren't fatal - we can live with the dynamic address */
	if (cdc_ether && cdc_ether->wMaxSegmentSize) {
		dev->hard_mtu = le16_to_cpu(cdc_ether->wMaxSegmentSize);
		usbnet_get_ethernet_addr(dev, cdc_ether->iMACAddress);
	}

	/* claim data interface and set it up */
	if (info->control != info->data) {
		status = usb_driver_claim_interface(driver, info->data, dev);
		if (status < 0)
			goto err;
	}

	status = qmi_wwan_register_subdriver(dev);
	if (status < 0 && info->control != info->data) {
		usb_set_intfdata(info->data, NULL);
		usb_driver_release_interface(driver, info->data);
	}

	/* disabling remote wakeup on MDM9x30 devices has the same
	 * effect as clearing DTR. The device will not respond to QMI
	 * requests until we set DTR again.  This is similar to a
	 * QMI_CTL SYNC request, clearing a lot of firmware state
	 * including the client ID allocations.
	 *
	 * Our usage model allows a session to span multiple
	 * open/close events, so we must prevent the firmware from
	 * clearing out state the clients might need.
	 *
	 * MDM9x30 is the first QMI chipset with USB3 support. Abuse
	 * this fact to enable the quirk for all USB3 devices.
	 *
	 * There are also chipsets with the same "set DTR" requirement
	 * but without USB3 support.  Devices based on these chips
	 * need a quirk flag in the device ID table.
	 */
	if (dev->driver_info->data & QMI_WWAN_QUIRK_DTR ||
	    le16_to_cpu(dev->udev->descriptor.bcdUSB) >= 0x0201) {
		qmi_wwan_manage_power(dev, 1);
		qmi_wwan_change_dtr(dev, true);
	}

	/* Never use the same address on both ends of the link, even if the
	 * buggy firmware told us to. Or, if device is assigned the well-known
	 * buggy firmware MAC address, replace it with a random address,
	 */
	if (ether_addr_equal(dev->net->dev_addr, default_modem_addr) ||
	    ether_addr_equal(dev->net->dev_addr, buggy_fw_addr))
		eth_hw_addr_random(dev->net);

	/* make MAC addr easily distinguishable from an IP header */
	if (possibly_iphdr(dev->net->dev_addr)) {
		dev->net->dev_addr[0] |= 0x02;	/* set local assignment bit */
		dev->net->dev_addr[0] &= 0xbf;	/* clear "IP" bit */
	}
	dev->net->netdev_ops = &qmi_wwan_netdev_ops;
	dev->net->sysfs_groups[0] = &qmi_wwan_sysfs_attr_group;
err:
	return status;
}