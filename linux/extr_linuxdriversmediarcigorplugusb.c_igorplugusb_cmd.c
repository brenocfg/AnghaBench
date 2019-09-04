#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bRequest; } ;
struct igorplugusb {int /*<<< orphan*/  dev; TYPE_2__* urb; TYPE_1__ request; } ;
struct TYPE_4__ {scalar_t__ transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igorplugusb_cmd(struct igorplugusb *ir, int cmd)
{
	int ret;

	ir->request.bRequest = cmd;
	ir->urb->transfer_flags = 0;
	ret = usb_submit_urb(ir->urb, GFP_ATOMIC);
	if (ret)
		dev_err(ir->dev, "submit urb failed: %d", ret);
}