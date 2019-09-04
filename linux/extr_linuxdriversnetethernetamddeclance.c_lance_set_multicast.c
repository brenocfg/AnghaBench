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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int flags; scalar_t__ mem_start; } ;
struct lance_regs {int /*<<< orphan*/  rdp; int /*<<< orphan*/  rap; } ;
struct lance_private {scalar_t__ tx_old; scalar_t__ tx_new; int /*<<< orphan*/  type; int /*<<< orphan*/  multicast_timer; struct lance_regs* ll; } ;

/* Variables and functions */
 int HZ ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  LE_MO_PROM ; 
 int /*<<< orphan*/  init_restart_lance (struct lance_private*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lance_init_ring (struct net_device*) ; 
 int /*<<< orphan*/  lance_load_multicast (struct net_device*) ; 
 int /*<<< orphan*/ * lib_ptr (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_csrs (struct lance_private*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mode ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lance_set_multicast(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile u16 *ib = (volatile u16 *)dev->mem_start;
	volatile struct lance_regs *ll = lp->ll;

	if (!netif_running(dev))
		return;

	if (lp->tx_old != lp->tx_new) {
		mod_timer(&lp->multicast_timer, jiffies + 4 * HZ/100);
		netif_wake_queue(dev);
		return;
	}

	netif_stop_queue(dev);

	writereg(&ll->rap, LE_CSR0);
	writereg(&ll->rdp, LE_C0_STOP);

	lance_init_ring(dev);

	if (dev->flags & IFF_PROMISC) {
		*lib_ptr(ib, mode, lp->type) |= LE_MO_PROM;
	} else {
		*lib_ptr(ib, mode, lp->type) &= ~LE_MO_PROM;
		lance_load_multicast(dev);
	}
	load_csrs(lp);
	init_restart_lance(lp);
	netif_wake_queue(dev);
}