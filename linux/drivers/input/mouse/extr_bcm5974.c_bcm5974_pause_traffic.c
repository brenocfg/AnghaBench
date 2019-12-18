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
struct bcm5974 {int /*<<< orphan*/  bt_urb; int /*<<< orphan*/  tp_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm5974_wellspring_mode (struct bcm5974*,int) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm5974_pause_traffic(struct bcm5974 *dev)
{
	usb_kill_urb(dev->tp_urb);
	usb_kill_urb(dev->bt_urb);
	bcm5974_wellspring_mode(dev, false);
}