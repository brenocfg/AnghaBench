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
struct bigmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bigmac_init_hw (struct bigmac*,int /*<<< orphan*/ ) ; 
 struct bigmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void bigmac_tx_timeout(struct net_device *dev)
{
	struct bigmac *bp = netdev_priv(dev);

	bigmac_init_hw(bp, 0);
	netif_wake_queue(dev);
}