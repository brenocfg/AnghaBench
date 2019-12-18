#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_ctrlrequest {int wLength; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct cdns3_device {int /*<<< orphan*/  setup_dma; int /*<<< orphan*/  dev; TYPE_1__ gadget; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ USB_STATE_ADDRESS ; 
 int /*<<< orphan*/  cdns3_ep0_run_transfer (struct cdns3_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cdns3_req_ep0_set_sel(struct cdns3_device *priv_dev,
				 struct usb_ctrlrequest *ctrl_req)
{
	if (priv_dev->gadget.state < USB_STATE_ADDRESS)
		return -EINVAL;

	if (ctrl_req->wLength != 6) {
		dev_err(priv_dev->dev, "Set SEL should be 6 bytes, got %d\n",
			ctrl_req->wLength);
		return -EINVAL;
	}

	cdns3_ep0_run_transfer(priv_dev, priv_dev->setup_dma, 6, 1, 0);
	return 0;
}