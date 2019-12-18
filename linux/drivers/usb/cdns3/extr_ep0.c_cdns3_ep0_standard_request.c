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
struct usb_ctrlrequest {int bRequest; } ;
struct cdns3_device {int dummy; } ;

/* Variables and functions */
#define  USB_REQ_CLEAR_FEATURE 134 
#define  USB_REQ_GET_STATUS 133 
#define  USB_REQ_SET_ADDRESS 132 
#define  USB_REQ_SET_CONFIGURATION 131 
#define  USB_REQ_SET_FEATURE 130 
#define  USB_REQ_SET_ISOCH_DELAY 129 
#define  USB_REQ_SET_SEL 128 
 int cdns3_ep0_delegate_req (struct cdns3_device*,struct usb_ctrlrequest*) ; 
 int cdns3_req_ep0_get_status (struct cdns3_device*,struct usb_ctrlrequest*) ; 
 int cdns3_req_ep0_handle_feature (struct cdns3_device*,struct usb_ctrlrequest*,int) ; 
 int cdns3_req_ep0_set_address (struct cdns3_device*,struct usb_ctrlrequest*) ; 
 int cdns3_req_ep0_set_configuration (struct cdns3_device*,struct usb_ctrlrequest*) ; 
 int cdns3_req_ep0_set_isoch_delay (struct cdns3_device*,struct usb_ctrlrequest*) ; 
 int cdns3_req_ep0_set_sel (struct cdns3_device*,struct usb_ctrlrequest*) ; 

__attribute__((used)) static int cdns3_ep0_standard_request(struct cdns3_device *priv_dev,
				      struct usb_ctrlrequest *ctrl_req)
{
	int ret;

	switch (ctrl_req->bRequest) {
	case USB_REQ_SET_ADDRESS:
		ret = cdns3_req_ep0_set_address(priv_dev, ctrl_req);
		break;
	case USB_REQ_SET_CONFIGURATION:
		ret = cdns3_req_ep0_set_configuration(priv_dev, ctrl_req);
		break;
	case USB_REQ_GET_STATUS:
		ret = cdns3_req_ep0_get_status(priv_dev, ctrl_req);
		break;
	case USB_REQ_CLEAR_FEATURE:
		ret = cdns3_req_ep0_handle_feature(priv_dev, ctrl_req, 0);
		break;
	case USB_REQ_SET_FEATURE:
		ret = cdns3_req_ep0_handle_feature(priv_dev, ctrl_req, 1);
		break;
	case USB_REQ_SET_SEL:
		ret = cdns3_req_ep0_set_sel(priv_dev, ctrl_req);
		break;
	case USB_REQ_SET_ISOCH_DELAY:
		ret = cdns3_req_ep0_set_isoch_delay(priv_dev, ctrl_req);
		break;
	default:
		ret = cdns3_ep0_delegate_req(priv_dev, ctrl_req);
		break;
	}

	return ret;
}