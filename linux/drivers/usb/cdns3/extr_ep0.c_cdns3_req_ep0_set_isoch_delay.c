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
struct usb_ctrlrequest {int /*<<< orphan*/  wValue; scalar_t__ wLength; scalar_t__ wIndex; } ;
struct cdns3_device {int /*<<< orphan*/  isoch_delay; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int cdns3_req_ep0_set_isoch_delay(struct cdns3_device *priv_dev,
					 struct usb_ctrlrequest *ctrl_req)
{
	if (ctrl_req->wIndex || ctrl_req->wLength)
		return -EINVAL;

	priv_dev->isoch_delay = ctrl_req->wValue;

	return 0;
}