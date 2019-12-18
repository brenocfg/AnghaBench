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
struct usb_ctrlrequest {int /*<<< orphan*/  wValue; } ;
struct cdns3_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_INTRF_FUNC_SUSPEND 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns3_ep0_feature_handle_intf(struct cdns3_device *priv_dev,
					 struct usb_ctrlrequest *ctrl,
					 int set)
{
	u32 wValue;
	int ret = 0;

	wValue = le16_to_cpu(ctrl->wValue);

	switch (wValue) {
	case USB_INTRF_FUNC_SUSPEND:
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}