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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; scalar_t__ collisions; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  name; scalar_t__ mem_start; } ;
struct lance_regs {int /*<<< orphan*/  rdp; int /*<<< orphan*/  rap; } ;
struct lance_private {int tx_old; int tx_new; int /*<<< orphan*/  lock; int /*<<< orphan*/  type; struct lance_regs* ll; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int LE_T1_EMORE ; 
 int LE_T1_EONE ; 
 int LE_T1_ERR ; 
 int LE_T1_OWN ; 
 int LE_T1_POK ; 
 int LE_T3_BUF ; 
 int LE_T3_CLOS ; 
 int LE_T3_LCOL ; 
 int LE_T3_RTY ; 
 int LE_T3_UFL ; 
 scalar_t__ TX_BUFFS_AVAIL ; 
 int TX_RING_MOD_MASK ; 
 int /*<<< orphan*/ * btx_ring ; 
 int /*<<< orphan*/  init_restart_lance (struct lance_private*) ; 
 int /*<<< orphan*/  lance_init_ring (struct net_device*) ; 
 int /*<<< orphan*/ * lib_ptr (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_csrs (struct lance_private*) ; 
 int /*<<< orphan*/  misc ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int* tds_ptr (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmd1 ; 
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lance_tx(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile u16 *ib = (volatile u16 *)dev->mem_start;
	volatile struct lance_regs *ll = lp->ll;
	volatile u16 *td;
	int i, j;
	int status;

	j = lp->tx_old;

	spin_lock(&lp->lock);

	for (i = j; i != lp->tx_new; i = j) {
		td = lib_ptr(ib, btx_ring[i], lp->type);
		/* If we hit a packet not owned by us, stop */
		if (*tds_ptr(td, tmd1, lp->type) & LE_T1_OWN)
			break;

		if (*tds_ptr(td, tmd1, lp->type) & LE_T1_ERR) {
			status = *tds_ptr(td, misc, lp->type);

			dev->stats.tx_errors++;
			if (status & LE_T3_RTY)
				dev->stats.tx_aborted_errors++;
			if (status & LE_T3_LCOL)
				dev->stats.tx_window_errors++;

			if (status & LE_T3_CLOS) {
				dev->stats.tx_carrier_errors++;
				printk("%s: Carrier Lost\n", dev->name);
				/* Stop the lance */
				writereg(&ll->rap, LE_CSR0);
				writereg(&ll->rdp, LE_C0_STOP);
				lance_init_ring(dev);
				load_csrs(lp);
				init_restart_lance(lp);
				goto out;
			}
			/* Buffer errors and underflows turn off the
			 * transmitter, restart the adapter.
			 */
			if (status & (LE_T3_BUF | LE_T3_UFL)) {
				dev->stats.tx_fifo_errors++;

				printk("%s: Tx: ERR_BUF|ERR_UFL, restarting\n",
				       dev->name);
				/* Stop the lance */
				writereg(&ll->rap, LE_CSR0);
				writereg(&ll->rdp, LE_C0_STOP);
				lance_init_ring(dev);
				load_csrs(lp);
				init_restart_lance(lp);
				goto out;
			}
		} else if ((*tds_ptr(td, tmd1, lp->type) & LE_T1_POK) ==
			   LE_T1_POK) {
			/*
			 * So we don't count the packet more than once.
			 */
			*tds_ptr(td, tmd1, lp->type) &= ~(LE_T1_POK);

			/* One collision before packet was sent. */
			if (*tds_ptr(td, tmd1, lp->type) & LE_T1_EONE)
				dev->stats.collisions++;

			/* More than one collision, be optimistic. */
			if (*tds_ptr(td, tmd1, lp->type) & LE_T1_EMORE)
				dev->stats.collisions += 2;

			dev->stats.tx_packets++;
		}
		j = (j + 1) & TX_RING_MOD_MASK;
	}
	lp->tx_old = j;
out:
	if (netif_queue_stopped(dev) &&
	    TX_BUFFS_AVAIL > 0)
		netif_wake_queue(dev);

	spin_unlock(&lp->lock);
}