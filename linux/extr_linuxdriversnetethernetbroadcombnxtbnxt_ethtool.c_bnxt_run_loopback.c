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
typedef  scalar_t__ u8 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct bnxt_tx_ring_info {int tx_prod; int /*<<< orphan*/  tx_doorbell; } ;
struct bnxt {TYPE_1__* pdev; TYPE_2__* dev; int /*<<< orphan*/  rx_copy_thresh; struct bnxt_tx_ring_info* tx_ring; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; scalar_t__ mtu; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DB_KEY_TX ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  bnxt_db_write (struct bnxt*,int /*<<< orphan*/ ,int) ; 
 int bnxt_poll_loopback (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_xmit_xdp (struct bnxt*,struct bnxt_tx_ring_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_broadcast_addr (scalar_t__*) ; 
 int /*<<< orphan*/  ether_addr_copy (scalar_t__*,int /*<<< orphan*/ ) ; 
 int min (scalar_t__,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (TYPE_2__*,int) ; 
 scalar_t__* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int bnxt_run_loopback(struct bnxt *bp)
{
	struct bnxt_tx_ring_info *txr = &bp->tx_ring[0];
	int pkt_size, i = 0;
	struct sk_buff *skb;
	dma_addr_t map;
	u8 *data;
	int rc;

	pkt_size = min(bp->dev->mtu + ETH_HLEN, bp->rx_copy_thresh);
	skb = netdev_alloc_skb(bp->dev, pkt_size);
	if (!skb)
		return -ENOMEM;
	data = skb_put(skb, pkt_size);
	eth_broadcast_addr(data);
	i += ETH_ALEN;
	ether_addr_copy(&data[i], bp->dev->dev_addr);
	i += ETH_ALEN;
	for ( ; i < pkt_size; i++)
		data[i] = (u8)(i & 0xff);

	map = dma_map_single(&bp->pdev->dev, skb->data, pkt_size,
			     PCI_DMA_TODEVICE);
	if (dma_mapping_error(&bp->pdev->dev, map)) {
		dev_kfree_skb(skb);
		return -EIO;
	}
	bnxt_xmit_xdp(bp, txr, map, pkt_size, 0);

	/* Sync BD data before updating doorbell */
	wmb();

	bnxt_db_write(bp, txr->tx_doorbell, DB_KEY_TX | txr->tx_prod);
	rc = bnxt_poll_loopback(bp, pkt_size);

	dma_unmap_single(&bp->pdev->dev, map, pkt_size, PCI_DMA_TODEVICE);
	dev_kfree_skb(skb);
	return rc;
}