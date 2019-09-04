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
struct lance_regs {int /*<<< orphan*/  rdp; } ;
struct lance_private {struct lance_regs* ll; } ;

/* Variables and functions */
 int /*<<< orphan*/  lance_reset (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void lance_tx_timeout(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile struct lance_regs *ll = lp->ll;

	netdev_err(dev, "transmit timed out, status %04x, reset\n", ll->rdp);
	lance_reset(dev);
	netif_wake_queue(dev);
}