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
struct peak_usb_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct peak_usb_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int peak_usb_start (struct peak_usb_device*) ; 

__attribute__((used)) static int peak_usb_ndo_open(struct net_device *netdev)
{
	struct peak_usb_device *dev = netdev_priv(netdev);
	int err;

	/* common open */
	err = open_candev(netdev);
	if (err)
		return err;

	/* finally start device */
	err = peak_usb_start(dev);
	if (err) {
		netdev_err(netdev, "couldn't start device: %d\n", err);
		close_candev(netdev);
		return err;
	}

	netif_start_queue(netdev);

	return 0;
}