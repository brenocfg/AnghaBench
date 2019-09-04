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
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct lance_private {int lance_log_tx_bufs; int lance_log_rx_bufs; scalar_t__ tx_old; scalar_t__ rx_old; scalar_t__ tx_new; scalar_t__ rx_new; struct lance_init_block* lance_init_block; struct lance_init_block* init_block; } ;
struct lance_init_block {int rx_len; int rx_ptr; int tx_len; int tx_ptr; scalar_t__* filter; TYPE_1__* btx_ring; TYPE_1__* brx_ring; TYPE_1__*** rx_buf; TYPE_1__*** tx_buf; int /*<<< orphan*/ * phys_addr; scalar_t__ mode; } ;
struct TYPE_2__ {int tmd0; int tmd1_hadr; int length; int rmd0; int rmd1_hadr; scalar_t__ mblength; int /*<<< orphan*/  rmd1_bits; scalar_t__ misc; scalar_t__ tmd1_bits; } ;

/* Variables and functions */
 int LANCE_ADDR (TYPE_1__**) ; 
 int /*<<< orphan*/  LE_R1_OWN ; 
 int RX_BUFF_SIZE ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static void lance_init_ring(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile struct lance_init_block *ib = lp->init_block;
	volatile struct lance_init_block *aib = lp->lance_init_block;
					/* for LANCE_ADDR computations */
	int leptr;
	int i;

	/* Lock out other processes while setting up hardware */
	netif_stop_queue(dev);
	lp->rx_new = lp->tx_new = 0;
	lp->rx_old = lp->tx_old = 0;

	ib->mode = 0;

	/* Copy the ethernet address to the lance init block
	 * Note that on the sparc you need to swap the ethernet address.
	 */
	ib->phys_addr[0] = dev->dev_addr[1];
	ib->phys_addr[1] = dev->dev_addr[0];
	ib->phys_addr[2] = dev->dev_addr[3];
	ib->phys_addr[3] = dev->dev_addr[2];
	ib->phys_addr[4] = dev->dev_addr[5];
	ib->phys_addr[5] = dev->dev_addr[4];

	/* Setup the Tx ring entries */
	netdev_dbg(dev, "TX rings:\n");
	for (i = 0; i <= 1 << lp->lance_log_tx_bufs; i++) {
		leptr = LANCE_ADDR(&aib->tx_buf[i][0]);
		ib->btx_ring[i].tmd0      = leptr;
		ib->btx_ring[i].tmd1_hadr = leptr >> 16;
		ib->btx_ring[i].tmd1_bits = 0;
		ib->btx_ring[i].length    = 0xf000; /* The ones required by tmd2 */
		ib->btx_ring[i].misc      = 0;
		if (i < 3)
			netdev_dbg(dev, "%d: 0x%08x\n", i, leptr);
	}

	/* Setup the Rx ring entries */
	netdev_dbg(dev, "RX rings:\n");
	for (i = 0; i < 1 << lp->lance_log_rx_bufs; i++) {
		leptr = LANCE_ADDR(&aib->rx_buf[i][0]);

		ib->brx_ring[i].rmd0      = leptr;
		ib->brx_ring[i].rmd1_hadr = leptr >> 16;
		ib->brx_ring[i].rmd1_bits = LE_R1_OWN;
		ib->brx_ring[i].length    = -RX_BUFF_SIZE | 0xf000;
		ib->brx_ring[i].mblength  = 0;
		if (i < 3)
			netdev_dbg(dev, "%d: 0x%08x\n", i, leptr);
	}

	/* Setup the initialization block */

	/* Setup rx descriptor pointer */
	leptr = LANCE_ADDR(&aib->brx_ring);
	ib->rx_len = (lp->lance_log_rx_bufs << 13) | (leptr >> 16);
	ib->rx_ptr = leptr;
	netdev_dbg(dev, "RX ptr: %08x\n", leptr);

	/* Setup tx descriptor pointer */
	leptr = LANCE_ADDR(&aib->btx_ring);
	ib->tx_len = (lp->lance_log_tx_bufs << 13) | (leptr >> 16);
	ib->tx_ptr = leptr;
	netdev_dbg(dev, "TX ptr: %08x\n", leptr);

	/* Clear the multicast filter */
	ib->filter[0] = 0;
	ib->filter[1] = 0;
}