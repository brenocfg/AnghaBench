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
struct esd_usb2_net_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int esd_usb2_start (struct esd_usb2_net_priv*) ; 
 struct esd_usb2_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 

__attribute__((used)) static int esd_usb2_open(struct net_device *netdev)
{
	struct esd_usb2_net_priv *priv = netdev_priv(netdev);
	int err;

	/* common open */
	err = open_candev(netdev);
	if (err)
		return err;

	/* finally start device */
	err = esd_usb2_start(priv);
	if (err) {
		netdev_warn(netdev, "couldn't start device: %d\n", err);
		close_candev(netdev);
		return err;
	}

	netif_start_queue(netdev);

	return 0;
}