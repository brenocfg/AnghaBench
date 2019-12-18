#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type_control; int dir_in; int dir_out; } ;
struct TYPE_6__ {int maxburst; int /*<<< orphan*/ * desc; int /*<<< orphan*/  name; TYPE_1__ caps; scalar_t__ address; int /*<<< orphan*/ * ops; } ;
struct cdns3_endpoint {int /*<<< orphan*/  type; TYPE_3__ endpoint; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_3__* ep0; } ;
struct cdns3_device {TYPE_2__ gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS3_EP0_MAX_PACKET_LIMIT ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_CONTROL ; 
 int cdns3_allocate_trb_pool (struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  cdns3_gadget_ep0_desc ; 
 int /*<<< orphan*/  cdns3_gadget_ep0_ops ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_3__*,int /*<<< orphan*/ ) ; 

int cdns3_init_ep0(struct cdns3_device *priv_dev,
		   struct cdns3_endpoint *priv_ep)
{
	sprintf(priv_ep->name, "ep0");

	/* fill linux fields */
	priv_ep->endpoint.ops = &cdns3_gadget_ep0_ops;
	priv_ep->endpoint.maxburst = 1;
	usb_ep_set_maxpacket_limit(&priv_ep->endpoint,
				   CDNS3_EP0_MAX_PACKET_LIMIT);
	priv_ep->endpoint.address = 0;
	priv_ep->endpoint.caps.type_control = 1;
	priv_ep->endpoint.caps.dir_in = 1;
	priv_ep->endpoint.caps.dir_out = 1;
	priv_ep->endpoint.name = priv_ep->name;
	priv_ep->endpoint.desc = &cdns3_gadget_ep0_desc;
	priv_dev->gadget.ep0 = &priv_ep->endpoint;
	priv_ep->type = USB_ENDPOINT_XFER_CONTROL;

	return cdns3_allocate_trb_pool(priv_ep);
}