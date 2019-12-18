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
struct TYPE_2__ {int /*<<< orphan*/  (* up ) (struct r8152*) ;} ;
struct r8152 {int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  flags; TYPE_1__ rtl_ops; struct net_device* netdev; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int IFF_UP ; 
 int /*<<< orphan*/  WORK_ENABLE ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct r8152*) ; 
 int /*<<< orphan*/  usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_system_resume(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;

	netif_device_attach(netdev);

	if (netif_running(netdev) && netdev->flags & IFF_UP) {
		tp->rtl_ops.up(tp);
		netif_carrier_off(netdev);
		set_bit(WORK_ENABLE, &tp->flags);
		usb_submit_urb(tp->intr_urb, GFP_NOIO);
	}

	return 0;
}