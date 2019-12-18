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
typedef  int u64 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct gem_txd {int dummy; } ;
struct gem_rxd {int /*<<< orphan*/  status_word; } ;
struct gem {int mac_rx_cfg; int swrst_base; int rx_pause_off; int rx_pause_on; scalar_t__ regs; scalar_t__ gblock_dvma; scalar_t__ rx_old; scalar_t__ rx_new; int /*<<< orphan*/ ** rx_skbs; TYPE_1__* init_block; struct net_device* dev; } ;
struct TYPE_2__ {struct gem_rxd* rxd; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 scalar_t__ GREG_BIFCFG ; 
 int GREG_BIFCFG_M66EN ; 
 scalar_t__ GREG_SWRST ; 
 int GREG_SWRST_RXRST ; 
 int INIT_BLOCK_TX_RING_SIZE ; 
 scalar_t__ MAC_RXCFG ; 
 int MAC_RXCFG_ENAB ; 
 scalar_t__ MAC_RXMASK ; 
 scalar_t__ MAC_RXRST ; 
 int MAC_RXRST_CMD ; 
 int MAC_RXSTAT_RCV ; 
 int /*<<< orphan*/  RXDCTRL_FRESH (struct gem*) ; 
 scalar_t__ RXDMA_BLANK ; 
 int RXDMA_BLANK_IPKTS ; 
 int RXDMA_BLANK_ITIME ; 
 scalar_t__ RXDMA_CFG ; 
 int RXDMA_CFG_BASE ; 
 int RXDMA_CFG_ENABLE ; 
 int RXDMA_CFG_FTHRESH_128 ; 
 scalar_t__ RXDMA_DBHI ; 
 scalar_t__ RXDMA_DBLOW ; 
 scalar_t__ RXDMA_KICK ; 
 scalar_t__ RXDMA_PTHRESH ; 
 int RXDMA_PTHRESH_OFF ; 
 int RXDMA_PTHRESH_ON ; 
 int RX_OFFSET ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int gem_rxmac_reset(struct gem *gp)
{
	struct net_device *dev = gp->dev;
	int limit, i;
	u64 desc_dma;
	u32 val;

	/* First, reset & disable MAC RX. */
	writel(MAC_RXRST_CMD, gp->regs + MAC_RXRST);
	for (limit = 0; limit < 5000; limit++) {
		if (!(readl(gp->regs + MAC_RXRST) & MAC_RXRST_CMD))
			break;
		udelay(10);
	}
	if (limit == 5000) {
		netdev_err(dev, "RX MAC will not reset, resetting whole chip\n");
		return 1;
	}

	writel(gp->mac_rx_cfg & ~MAC_RXCFG_ENAB,
	       gp->regs + MAC_RXCFG);
	for (limit = 0; limit < 5000; limit++) {
		if (!(readl(gp->regs + MAC_RXCFG) & MAC_RXCFG_ENAB))
			break;
		udelay(10);
	}
	if (limit == 5000) {
		netdev_err(dev, "RX MAC will not disable, resetting whole chip\n");
		return 1;
	}

	/* Second, disable RX DMA. */
	writel(0, gp->regs + RXDMA_CFG);
	for (limit = 0; limit < 5000; limit++) {
		if (!(readl(gp->regs + RXDMA_CFG) & RXDMA_CFG_ENABLE))
			break;
		udelay(10);
	}
	if (limit == 5000) {
		netdev_err(dev, "RX DMA will not disable, resetting whole chip\n");
		return 1;
	}

	mdelay(5);

	/* Execute RX reset command. */
	writel(gp->swrst_base | GREG_SWRST_RXRST,
	       gp->regs + GREG_SWRST);
	for (limit = 0; limit < 5000; limit++) {
		if (!(readl(gp->regs + GREG_SWRST) & GREG_SWRST_RXRST))
			break;
		udelay(10);
	}
	if (limit == 5000) {
		netdev_err(dev, "RX reset command will not execute, resetting whole chip\n");
		return 1;
	}

	/* Refresh the RX ring. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		struct gem_rxd *rxd = &gp->init_block->rxd[i];

		if (gp->rx_skbs[i] == NULL) {
			netdev_err(dev, "Parts of RX ring empty, resetting whole chip\n");
			return 1;
		}

		rxd->status_word = cpu_to_le64(RXDCTRL_FRESH(gp));
	}
	gp->rx_new = gp->rx_old = 0;

	/* Now we must reprogram the rest of RX unit. */
	desc_dma = (u64) gp->gblock_dvma;
	desc_dma += (INIT_BLOCK_TX_RING_SIZE * sizeof(struct gem_txd));
	writel(desc_dma >> 32, gp->regs + RXDMA_DBHI);
	writel(desc_dma & 0xffffffff, gp->regs + RXDMA_DBLOW);
	writel(RX_RING_SIZE - 4, gp->regs + RXDMA_KICK);
	val = (RXDMA_CFG_BASE | (RX_OFFSET << 10) |
	       (ETH_HLEN << 13) | RXDMA_CFG_FTHRESH_128);
	writel(val, gp->regs + RXDMA_CFG);
	if (readl(gp->regs + GREG_BIFCFG) & GREG_BIFCFG_M66EN)
		writel(((5 & RXDMA_BLANK_IPKTS) |
			((8 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
	else
		writel(((5 & RXDMA_BLANK_IPKTS) |
			((4 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
	val  = (((gp->rx_pause_off / 64) << 0) & RXDMA_PTHRESH_OFF);
	val |= (((gp->rx_pause_on / 64) << 12) & RXDMA_PTHRESH_ON);
	writel(val, gp->regs + RXDMA_PTHRESH);
	val = readl(gp->regs + RXDMA_CFG);
	writel(val | RXDMA_CFG_ENABLE, gp->regs + RXDMA_CFG);
	writel(MAC_RXSTAT_RCV, gp->regs + MAC_RXMASK);
	val = readl(gp->regs + MAC_RXCFG);
	writel(val | MAC_RXCFG_ENAB, gp->regs + MAC_RXCFG);

	return 0;
}