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
struct net_device {unsigned long base_addr; int* dev_addr; scalar_t__ dma; int /*<<< orphan*/ * netdev_ops; } ;
struct lance_init_block {int dummy; } ;
struct TYPE_4__ {unsigned long base; int /*<<< orphan*/  tx_ring_mod_mask; int /*<<< orphan*/  rx_ring_mod_mask; int /*<<< orphan*/  lance_log_tx_bufs; int /*<<< orphan*/  lance_log_rx_bufs; int /*<<< orphan*/  readrdp; int /*<<< orphan*/  writerdp; int /*<<< orphan*/  writerap; int /*<<< orphan*/  irq; int /*<<< orphan*/  busmaster_regval; int /*<<< orphan*/ * lance_init_block; struct lance_init_block* init_block; int /*<<< orphan*/  name; } ;
struct hplance_private {TYPE_2__ lance; } ;
struct TYPE_3__ {unsigned long start; } ;
struct dio_dev {int /*<<< orphan*/  ipl; int /*<<< orphan*/  name; TYPE_1__ resource; } ;

/* Variables and functions */
 scalar_t__ DIO_IDOFF ; 
 unsigned long DIO_VIRADDRBASE ; 
 scalar_t__ HPLANCE_MEMOFF ; 
 scalar_t__ HPLANCE_NVRAMOFF ; 
 int /*<<< orphan*/  LANCE_LOG_RX_BUFFERS ; 
 int /*<<< orphan*/  LANCE_LOG_TX_BUFFERS ; 
 int /*<<< orphan*/  LE_C3_BSWP ; 
 int /*<<< orphan*/  RX_RING_MOD_MASK ; 
 int /*<<< orphan*/  TX_RING_MOD_MASK ; 
 int /*<<< orphan*/  hplance_netdev_ops ; 
 int /*<<< orphan*/  hplance_readrdp ; 
 int /*<<< orphan*/  hplance_writerap ; 
 int /*<<< orphan*/  hplance_writerdp ; 
 int in_8 (scalar_t__) ; 
 struct hplance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  out_8 (scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void hplance_init(struct net_device *dev, struct dio_dev *d)
{
	unsigned long va = (d->resource.start + DIO_VIRADDRBASE);
	struct hplance_private *lp;
	int i;

	/* reset the board */
	out_8(va + DIO_IDOFF, 0xff);
	udelay(100);                              /* ariba! ariba! udelay! udelay! */

	/* Fill the dev fields */
	dev->base_addr = va;
	dev->netdev_ops = &hplance_netdev_ops;
	dev->dma = 0;

	for (i = 0; i < 6; i++) {
		/* The NVRAM holds our ethernet address, one nibble per byte,
		 * at bytes NVRAMOFF+1,3,5,7,9...
		 */
		dev->dev_addr[i] = ((in_8(va + HPLANCE_NVRAMOFF + i*4 + 1) & 0xF) << 4)
			| (in_8(va + HPLANCE_NVRAMOFF + i*4 + 3) & 0xF);
	}

	lp = netdev_priv(dev);
	lp->lance.name = d->name;
	lp->lance.base = va;
	lp->lance.init_block = (struct lance_init_block *)(va + HPLANCE_MEMOFF); /* CPU addr */
	lp->lance.lance_init_block = NULL;              /* LANCE addr of same RAM */
	lp->lance.busmaster_regval = LE_C3_BSWP;        /* we're bigendian */
	lp->lance.irq = d->ipl;
	lp->lance.writerap = hplance_writerap;
	lp->lance.writerdp = hplance_writerdp;
	lp->lance.readrdp = hplance_readrdp;
	lp->lance.lance_log_rx_bufs = LANCE_LOG_RX_BUFFERS;
	lp->lance.lance_log_tx_bufs = LANCE_LOG_TX_BUFFERS;
	lp->lance.rx_ring_mod_mask = RX_RING_MOD_MASK;
	lp->lance.tx_ring_mod_mask = TX_RING_MOD_MASK;
}