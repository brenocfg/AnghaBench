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
typedef  size_t u8 ;
struct usb_ctrlrequest {int wIndex; int /*<<< orphan*/  wValue; } ;
struct cdns3_endpoint {int flags; } ;
struct cdns3_device {struct cdns3_endpoint** eps; } ;

/* Variables and functions */
 int EINVAL ; 
 int EP_WEDGE ; 
 int USB_DIR_IN ; 
 scalar_t__ USB_ENDPOINT_HALT ; 
 int __cdns3_gadget_ep_clear_halt (struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  __cdns3_gadget_ep_set_halt (struct cdns3_endpoint*) ; 
 size_t cdns3_ep_addr_to_index (int) ; 
 int /*<<< orphan*/  cdns3_select_ep (struct cdns3_device*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns3_ep0_feature_handle_endpoint(struct cdns3_device *priv_dev,
					     struct usb_ctrlrequest *ctrl,
					     int set)
{
	struct cdns3_endpoint *priv_ep;
	int ret = 0;
	u8 index;

	if (le16_to_cpu(ctrl->wValue) != USB_ENDPOINT_HALT)
		return -EINVAL;

	if (!(ctrl->wIndex & ~USB_DIR_IN))
		return 0;

	index = cdns3_ep_addr_to_index(ctrl->wIndex);
	priv_ep = priv_dev->eps[index];

	cdns3_select_ep(priv_dev, ctrl->wIndex);

	if (set)
		__cdns3_gadget_ep_set_halt(priv_ep);
	else if (!(priv_ep->flags & EP_WEDGE))
		ret = __cdns3_gadget_ep_clear_halt(priv_ep);

	cdns3_select_ep(priv_dev, 0x00);

	return ret;
}