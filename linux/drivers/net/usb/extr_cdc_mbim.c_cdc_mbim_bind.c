#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usbnet {TYPE_4__* net; TYPE_3__* status; TYPE_1__* driver_info; int /*<<< orphan*/  data; } ;
struct usb_interface {int /*<<< orphan*/  cur_altsetting; } ;
struct usb_driver {int dummy; } ;
struct cdc_ncm_ctx {TYPE_2__* mbim_desc; int /*<<< orphan*/  control; } ;
struct cdc_mbim_state {struct usb_driver* subdriver; struct cdc_ncm_ctx* ctx; } ;
struct TYPE_8__ {int features; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  wMaxControlMessage; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ CDC_NCM_COMM_ALTSETTING_MBIM ; 
 int CDC_NCM_DATA_ALTSETTING_MBIM ; 
 int ENODEV ; 
 struct usb_driver* ERR_PTR (int) ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 scalar_t__ IS_ERR (struct usb_driver*) ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int PTR_ERR (struct usb_driver*) ; 
 int /*<<< orphan*/  cdc_mbim_netdev_ops ; 
 int cdc_mbim_set_ctrlalt (struct usbnet*,struct usb_interface*,scalar_t__) ; 
 int /*<<< orphan*/  cdc_mbim_wdm_manage_power ; 
 int cdc_ncm_bind_common (struct usbnet*,struct usb_interface*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdc_ncm_comm_intf_is_mbim (int /*<<< orphan*/ ) ; 
 scalar_t__ cdc_ncm_select_altsetting (struct usb_interface*) ; 
 int /*<<< orphan*/  cdc_ncm_unbind (struct usbnet*,struct usb_interface*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct usb_driver* usb_cdc_wdm_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdc_mbim_bind(struct usbnet *dev, struct usb_interface *intf)
{
	struct cdc_ncm_ctx *ctx;
	struct usb_driver *subdriver = ERR_PTR(-ENODEV);
	int ret = -ENODEV;
	u8 data_altsetting = 1;
	struct cdc_mbim_state *info = (void *)&dev->data;

	/* should we change control altsetting on a NCM/MBIM function? */
	if (cdc_ncm_select_altsetting(intf) == CDC_NCM_COMM_ALTSETTING_MBIM) {
		data_altsetting = CDC_NCM_DATA_ALTSETTING_MBIM;
		ret = cdc_mbim_set_ctrlalt(dev, intf, CDC_NCM_COMM_ALTSETTING_MBIM);
		if (ret)
			goto err;
		ret = -ENODEV;
	}

	/* we will hit this for NCM/MBIM functions if prefer_mbim is false */
	if (!cdc_ncm_comm_intf_is_mbim(intf->cur_altsetting))
		goto err;

	ret = cdc_ncm_bind_common(dev, intf, data_altsetting, dev->driver_info->data);
	if (ret)
		goto err;

	ctx = info->ctx;

	/* The MBIM descriptor and the status endpoint are required */
	if (ctx->mbim_desc && dev->status)
		subdriver = usb_cdc_wdm_register(ctx->control,
						 &dev->status->desc,
						 le16_to_cpu(ctx->mbim_desc->wMaxControlMessage),
						 cdc_mbim_wdm_manage_power);
	if (IS_ERR(subdriver)) {
		ret = PTR_ERR(subdriver);
		cdc_ncm_unbind(dev, intf);
		goto err;
	}

	/* can't let usbnet use the interrupt endpoint */
	dev->status = NULL;
	info->subdriver = subdriver;

	/* MBIM cannot do ARP */
	dev->net->flags |= IFF_NOARP;

	/* no need to put the VLAN tci in the packet headers */
	dev->net->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_FILTER;

	/* monitor VLAN additions and removals */
	dev->net->netdev_ops = &cdc_mbim_netdev_ops;
err:
	return ret;
}