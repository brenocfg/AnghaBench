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
struct urb {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct hfa384x {int /*<<< orphan*/  usb_work; int /*<<< orphan*/  usb_flags; TYPE_1__* wlandev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct net_device* netdev; int /*<<< orphan*/  hwremoved; } ;

/* Variables and functions */
 int ENOLINK ; 
 int EPIPE ; 
 int /*<<< orphan*/  WORK_TX_HALT ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int submit_tx_urb(struct hfa384x *hw, struct urb *tx_urb, gfp_t memflags)
{
	struct net_device *netdev = hw->wlandev->netdev;
	int result;

	result = -ENOLINK;
	if (netif_running(netdev)) {
		if (!hw->wlandev->hwremoved &&
		    !test_bit(WORK_TX_HALT, &hw->usb_flags)) {
			result = usb_submit_urb(tx_urb, memflags);

			/* Test whether we need to reset the TX pipe */
			if (result == -EPIPE) {
				netdev_warn(hw->wlandev->netdev,
					    "%s tx pipe stalled: requesting reset\n",
					    netdev->name);
				set_bit(WORK_TX_HALT, &hw->usb_flags);
				schedule_work(&hw->usb_work);
			} else if (result == 0) {
				netif_stop_queue(netdev);
			}
		}
	}

	return result;
}