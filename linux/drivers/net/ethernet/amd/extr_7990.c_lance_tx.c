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
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; scalar_t__ collisions; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct lance_tx_desc {int tmd1_bits; int misc; } ;
struct lance_private {int tx_old; int tx_new; int tx_ring_mod_mask; scalar_t__ tpe; scalar_t__ auto_select; struct lance_init_block* init_block; } ;
struct lance_init_block {struct lance_tx_desc* btx_ring; } ;

/* Variables and functions */
 int LE_C0_INEA ; 
 int LE_C0_STOP ; 
 int LE_C0_TINT ; 
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
 int /*<<< orphan*/  WRITERAP (struct lance_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITERDP (struct lance_private*,int) ; 
 int /*<<< orphan*/  blinken_leds (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_restart_lance (struct lance_private*) ; 
 int /*<<< orphan*/  lance_init_ring (struct net_device*) ; 
 int /*<<< orphan*/  load_csrs (struct lance_private*) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int lance_tx(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile struct lance_init_block *ib = lp->init_block;
	volatile struct lance_tx_desc *td;
	int i, j;
	int status;

#ifdef CONFIG_HP300
	blinken_leds(0x80, 0);
#endif
	/* csr0 is 2f3 */
	WRITERDP(lp, LE_C0_TINT | LE_C0_INEA);
	/* csr0 is 73 */

	j = lp->tx_old;
	for (i = j; i != lp->tx_new; i = j) {
		td = &ib->btx_ring[i];

		/* If we hit a packet not owned by us, stop */
		if (td->tmd1_bits & LE_T1_OWN)
			break;

		if (td->tmd1_bits & LE_T1_ERR) {
			status = td->misc;

			dev->stats.tx_errors++;
			if (status & LE_T3_RTY)
				dev->stats.tx_aborted_errors++;
			if (status & LE_T3_LCOL)
				dev->stats.tx_window_errors++;

			if (status & LE_T3_CLOS) {
				dev->stats.tx_carrier_errors++;
				if (lp->auto_select) {
					lp->tpe = 1 - lp->tpe;
					printk("%s: Carrier Lost, trying %s\n",
					       dev->name,
					       lp->tpe ? "TPE" : "AUI");
					/* Stop the lance */
					WRITERAP(lp, LE_CSR0);
					WRITERDP(lp, LE_C0_STOP);
					lance_init_ring(dev);
					load_csrs(lp);
					init_restart_lance(lp);
					return 0;
				}
			}

			/* buffer errors and underflows turn off the transmitter */
			/* Restart the adapter */
			if (status & (LE_T3_BUF|LE_T3_UFL)) {
				dev->stats.tx_fifo_errors++;

				printk("%s: Tx: ERR_BUF|ERR_UFL, restarting\n",
				       dev->name);
				/* Stop the lance */
				WRITERAP(lp, LE_CSR0);
				WRITERDP(lp, LE_C0_STOP);
				lance_init_ring(dev);
				load_csrs(lp);
				init_restart_lance(lp);
				return 0;
			}
		} else if ((td->tmd1_bits & LE_T1_POK) == LE_T1_POK) {
			/*
			 * So we don't count the packet more than once.
			 */
			td->tmd1_bits &= ~(LE_T1_POK);

			/* One collision before packet was sent. */
			if (td->tmd1_bits & LE_T1_EONE)
				dev->stats.collisions++;

			/* More than one collision, be optimistic. */
			if (td->tmd1_bits & LE_T1_EMORE)
				dev->stats.collisions += 2;

			dev->stats.tx_packets++;
		}

		j = (j + 1) & lp->tx_ring_mod_mask;
	}
	lp->tx_old = j;
	WRITERDP(lp, LE_C0_TINT | LE_C0_INEA);
	return 0;
}