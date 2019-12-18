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
typedef  int u64 ;
typedef  int u32 ;
struct tx_ring_info {int tx_channel; int max_burst; int descr_dma; int pending; int mbox_dma; scalar_t__ last_pkt_cnt; } ;
struct niu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TXC_DMA_MAX (int) ; 
 int /*<<< orphan*/  TXDMA_MBH (int) ; 
 int TXDMA_MBH_MBADDR ; 
 int /*<<< orphan*/  TXDMA_MBL (int) ; 
 int TXDMA_MBL_MBADDR ; 
 int /*<<< orphan*/  TX_CS (int) ; 
 int /*<<< orphan*/  TX_ENT_MSK (int) ; 
 int /*<<< orphan*/  TX_RNG_CFIG (int) ; 
 int TX_RNG_CFIG_LEN_SHIFT ; 
 int TX_RNG_CFIG_STADDR ; 
 int TX_RNG_CFIG_STADDR_BASE ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,unsigned long long) ; 
 int niu_tx_channel_lpage_init (struct niu*,int) ; 
 int niu_tx_channel_reset (struct niu*,int) ; 
 int niu_tx_channel_stop (struct niu*,int) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_init_one_tx_channel(struct niu *np, struct tx_ring_info *rp)
{
	int err, channel = rp->tx_channel;
	u64 val, ring_len;

	err = niu_tx_channel_stop(np, channel);
	if (err)
		return err;

	err = niu_tx_channel_reset(np, channel);
	if (err)
		return err;

	err = niu_tx_channel_lpage_init(np, channel);
	if (err)
		return err;

	nw64(TXC_DMA_MAX(channel), rp->max_burst);
	nw64(TX_ENT_MSK(channel), 0);

	if (rp->descr_dma & ~(TX_RNG_CFIG_STADDR_BASE |
			      TX_RNG_CFIG_STADDR)) {
		netdev_err(np->dev, "TX ring channel %d DMA addr (%llx) is not aligned\n",
			   channel, (unsigned long long)rp->descr_dma);
		return -EINVAL;
	}

	/* The length field in TX_RNG_CFIG is measured in 64-byte
	 * blocks.  rp->pending is the number of TX descriptors in
	 * our ring, 8 bytes each, thus we divide by 8 bytes more
	 * to get the proper value the chip wants.
	 */
	ring_len = (rp->pending / 8);

	val = ((ring_len << TX_RNG_CFIG_LEN_SHIFT) |
	       rp->descr_dma);
	nw64(TX_RNG_CFIG(channel), val);

	if (((rp->mbox_dma >> 32) & ~TXDMA_MBH_MBADDR) ||
	    ((u32)rp->mbox_dma & ~TXDMA_MBL_MBADDR)) {
		netdev_err(np->dev, "TX ring channel %d MBOX addr (%llx) has invalid bits\n",
			    channel, (unsigned long long)rp->mbox_dma);
		return -EINVAL;
	}
	nw64(TXDMA_MBH(channel), rp->mbox_dma >> 32);
	nw64(TXDMA_MBL(channel), rp->mbox_dma & TXDMA_MBL_MBADDR);

	nw64(TX_CS(channel), 0);

	rp->last_pkt_cnt = 0;

	return 0;
}