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
struct lan78xx_net {int /*<<< orphan*/  bh; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_urbs (struct lan78xx_net*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan78xx_tx_timeout(struct net_device *net)
{
	struct lan78xx_net *dev = netdev_priv(net);

	unlink_urbs(dev, &dev->txq);
	tasklet_schedule(&dev->bh);
}