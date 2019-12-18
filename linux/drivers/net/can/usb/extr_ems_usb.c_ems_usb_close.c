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
struct net_device {int dummy; } ;
struct ems_usb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SJA1000_MOD_RM ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 scalar_t__ ems_usb_write_mode (struct ems_usb*,int /*<<< orphan*/ ) ; 
 struct ems_usb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  unlink_all_urbs (struct ems_usb*) ; 

__attribute__((used)) static int ems_usb_close(struct net_device *netdev)
{
	struct ems_usb *dev = netdev_priv(netdev);

	/* Stop polling */
	unlink_all_urbs(dev);

	netif_stop_queue(netdev);

	/* Set CAN controller to reset mode */
	if (ems_usb_write_mode(dev, SJA1000_MOD_RM))
		netdev_warn(netdev, "couldn't stop device");

	close_candev(netdev);

	return 0;
}