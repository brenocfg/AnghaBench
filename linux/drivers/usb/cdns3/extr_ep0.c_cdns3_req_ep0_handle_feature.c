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
typedef  int u32 ;
struct usb_ctrlrequest {int bRequestType; } ;
struct cdns3_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int cdns3_ep0_feature_handle_device (struct cdns3_device*,struct usb_ctrlrequest*,int) ; 
 int cdns3_ep0_feature_handle_endpoint (struct cdns3_device*,struct usb_ctrlrequest*,int) ; 
 int cdns3_ep0_feature_handle_intf (struct cdns3_device*,struct usb_ctrlrequest*,int) ; 

__attribute__((used)) static int cdns3_req_ep0_handle_feature(struct cdns3_device *priv_dev,
					struct usb_ctrlrequest *ctrl,
					int set)
{
	int ret = 0;
	u32 recip;

	recip = ctrl->bRequestType & USB_RECIP_MASK;

	switch (recip) {
	case USB_RECIP_DEVICE:
		ret = cdns3_ep0_feature_handle_device(priv_dev, ctrl, set);
		break;
	case USB_RECIP_INTERFACE:
		ret = cdns3_ep0_feature_handle_intf(priv_dev, ctrl, set);
		break;
	case USB_RECIP_ENDPOINT:
		ret = cdns3_ep0_feature_handle_endpoint(priv_dev, ctrl, set);
		break;
	default:
		return -EINVAL;
	}

	return ret;
}