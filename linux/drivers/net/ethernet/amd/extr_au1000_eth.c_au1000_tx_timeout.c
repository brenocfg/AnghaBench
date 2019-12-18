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

/* Variables and functions */
 int /*<<< orphan*/  au1000_init (struct net_device*) ; 
 int /*<<< orphan*/  au1000_reset_mac (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void au1000_tx_timeout(struct net_device *dev)
{
	netdev_err(dev, "au1000_tx_timeout: dev=%p\n", dev);
	au1000_reset_mac(dev);
	au1000_init(dev);
	netif_trans_update(dev); /* prevent tx timeout */
	netif_wake_queue(dev);
}