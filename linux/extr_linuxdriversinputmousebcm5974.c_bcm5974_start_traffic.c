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
struct bcm5974 {scalar_t__ bt_urb; scalar_t__ tp_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bcm5974_wellspring_mode (struct bcm5974*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 
 int usb_submit_urb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm5974_start_traffic(struct bcm5974 *dev)
{
	int error;

	error = bcm5974_wellspring_mode(dev, true);
	if (error) {
		dprintk(1, "bcm5974: mode switch failed\n");
		goto err_out;
	}

	if (dev->bt_urb) {
		error = usb_submit_urb(dev->bt_urb, GFP_KERNEL);
		if (error)
			goto err_reset_mode;
	}

	error = usb_submit_urb(dev->tp_urb, GFP_KERNEL);
	if (error)
		goto err_kill_bt;

	return 0;

err_kill_bt:
	usb_kill_urb(dev->bt_urb);
err_reset_mode:
	bcm5974_wellspring_mode(dev, false);
err_out:
	return error;
}