#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct lance_private {scalar_t__ tx_old; scalar_t__ rx_old; scalar_t__ tx_new; scalar_t__ rx_new; scalar_t__ init_block_dvma; struct lance_init_block* init_block_mem; } ;
struct lance_init_block {int rx_len; int rx_ptr; int tx_len; int tx_ptr; TYPE_2__* brx_ring; TYPE_1__* btx_ring; int /*<<< orphan*/ * phys_addr; } ;
typedef  scalar_t__ dma_addr_t ;
typedef  int __u32 ;
struct TYPE_4__ {int rmd0; int rmd1_hadr; int length; scalar_t__ mblength; int /*<<< orphan*/  rmd1_bits; } ;
struct TYPE_3__ {int tmd0; int tmd1_hadr; int length; scalar_t__ misc; scalar_t__ tmd1_bits; } ;

/* Variables and functions */
 int LANCE_ADDR (scalar_t__) ; 
 int LANCE_LOG_RX_BUFFERS ; 
 int LANCE_LOG_TX_BUFFERS ; 
 int /*<<< orphan*/  LE_R1_OWN ; 
 int RX_BUFF_SIZE ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  brx_ring ; 
 int /*<<< orphan*/  btx_ring ; 
 scalar_t__ libbuff_offset (int /*<<< orphan*/ ,int) ; 
 scalar_t__ libdesc_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rx_buf ; 
 int /*<<< orphan*/  tx_buf ; 

__attribute__((used)) static void lance_init_ring_dvma(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	struct lance_init_block *ib = lp->init_block_mem;
	dma_addr_t aib = lp->init_block_dvma;
	__u32 leptr;
	int i;

	/* Lock out other processes while setting up hardware */
	netif_stop_queue(dev);
	lp->rx_new = lp->tx_new = 0;
	lp->rx_old = lp->tx_old = 0;

	/* Copy the ethernet address to the lance init block
	 * Note that on the sparc you need to swap the ethernet address.
	 */
	ib->phys_addr [0] = dev->dev_addr [1];
	ib->phys_addr [1] = dev->dev_addr [0];
	ib->phys_addr [2] = dev->dev_addr [3];
	ib->phys_addr [3] = dev->dev_addr [2];
	ib->phys_addr [4] = dev->dev_addr [5];
	ib->phys_addr [5] = dev->dev_addr [4];

	/* Setup the Tx ring entries */
	for (i = 0; i < TX_RING_SIZE; i++) {
		leptr = LANCE_ADDR(aib + libbuff_offset(tx_buf, i));
		ib->btx_ring [i].tmd0      = leptr;
		ib->btx_ring [i].tmd1_hadr = leptr >> 16;
		ib->btx_ring [i].tmd1_bits = 0;
		ib->btx_ring [i].length    = 0xf000; /* The ones required by tmd2 */
		ib->btx_ring [i].misc      = 0;
	}

	/* Setup the Rx ring entries */
	for (i = 0; i < RX_RING_SIZE; i++) {
		leptr = LANCE_ADDR(aib + libbuff_offset(rx_buf, i));

		ib->brx_ring [i].rmd0      = leptr;
		ib->brx_ring [i].rmd1_hadr = leptr >> 16;
		ib->brx_ring [i].rmd1_bits = LE_R1_OWN;
		ib->brx_ring [i].length    = -RX_BUFF_SIZE | 0xf000;
		ib->brx_ring [i].mblength  = 0;
	}

	/* Setup the initialization block */

	/* Setup rx descriptor pointer */
	leptr = LANCE_ADDR(aib + libdesc_offset(brx_ring, 0));
	ib->rx_len = (LANCE_LOG_RX_BUFFERS << 13) | (leptr >> 16);
	ib->rx_ptr = leptr;

	/* Setup tx descriptor pointer */
	leptr = LANCE_ADDR(aib + libdesc_offset(btx_ring, 0));
	ib->tx_len = (LANCE_LOG_TX_BUFFERS << 13) | (leptr >> 16);
	ib->tx_ptr = leptr;
}