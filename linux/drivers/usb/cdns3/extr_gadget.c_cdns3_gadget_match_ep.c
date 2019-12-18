#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_ss_ep_comp_descriptor {int dummy; } ;
struct usb_gadget {int dummy; } ;
struct usb_ep {struct usb_endpoint_descriptor* desc; } ;
struct usb_endpoint_descriptor {scalar_t__ bInterval; } ;
struct cdns3_endpoint {struct usb_ep endpoint; int /*<<< orphan*/  interval; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  dir; int /*<<< orphan*/  name; } ;
struct cdns3_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int /*<<< orphan*/  EP_CLAIMED ; 
 scalar_t__ IS_ERR (struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 struct cdns3_endpoint* cdns3_find_available_ep (struct cdns3_device*,struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct cdns3_device* gadget_to_cdns3_device (struct usb_gadget*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_endpoint_type (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static struct
usb_ep *cdns3_gadget_match_ep(struct usb_gadget *gadget,
			      struct usb_endpoint_descriptor *desc,
			      struct usb_ss_ep_comp_descriptor *comp_desc)
{
	struct cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);
	struct cdns3_endpoint *priv_ep;
	unsigned long flags;

	priv_ep = cdns3_find_available_ep(priv_dev, desc);
	if (IS_ERR(priv_ep)) {
		dev_err(priv_dev->dev, "no available ep\n");
		return NULL;
	}

	dev_dbg(priv_dev->dev, "match endpoint: %s\n", priv_ep->name);

	spin_lock_irqsave(&priv_dev->lock, flags);
	priv_ep->endpoint.desc = desc;
	priv_ep->dir  = usb_endpoint_dir_in(desc) ? USB_DIR_IN : USB_DIR_OUT;
	priv_ep->type = usb_endpoint_type(desc);
	priv_ep->flags |= EP_CLAIMED;
	priv_ep->interval = desc->bInterval ? BIT(desc->bInterval - 1) : 0;

	spin_unlock_irqrestore(&priv_dev->lock, flags);
	return &priv_ep->endpoint;
}