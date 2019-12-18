#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct b44 {int tx_ring_dma; int dma_offset; int rx_ring_dma; int rx_pending; int rx_prod; TYPE_1__* dev; } ;
struct TYPE_3__ {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_CHIP_RESET_FULL ; 
 int /*<<< orphan*/  B44_DMARX_ADDR ; 
 int /*<<< orphan*/  B44_DMARX_CTRL ; 
 int /*<<< orphan*/  B44_DMARX_PTR ; 
 int /*<<< orphan*/  B44_DMATX_ADDR ; 
 int /*<<< orphan*/  B44_DMATX_CTRL ; 
 int /*<<< orphan*/  B44_ENET_CTRL ; 
 int B44_FULL_RESET ; 
 int /*<<< orphan*/  B44_MAC_CTRL ; 
 int /*<<< orphan*/  B44_MIB_CTRL ; 
 int B44_PARTIAL_RESET ; 
 int /*<<< orphan*/  B44_RCV_LAZY ; 
 int /*<<< orphan*/  B44_RXMAXLEN ; 
 int /*<<< orphan*/  B44_TXMAXLEN ; 
 int /*<<< orphan*/  B44_TX_WMARK ; 
 int DMARX_CTRL_ENABLE ; 
 int DMARX_CTRL_ROSHIFT ; 
 int DMATX_CTRL_ENABLE ; 
 int ENET_CTRL_ENABLE ; 
 int ETH_HLEN ; 
 int MAC_CTRL_CRC32_ENAB ; 
 int MAC_CTRL_PHY_LEDCTRL ; 
 int MIB_CTRL_CLR_ON_READ ; 
 int RCV_LAZY_FC_SHIFT ; 
 int RX_HEADER_LEN ; 
 int RX_PKT_OFFSET ; 
 int /*<<< orphan*/  __b44_set_rx_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  b44_chip_reset (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_phy_reset (struct b44*) ; 
 int /*<<< orphan*/  b44_setup_phy (struct b44*) ; 
 int br32 (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_reset_queue (TYPE_1__*) ; 

__attribute__((used)) static void b44_init_hw(struct b44 *bp, int reset_kind)
{
	u32 val;

	b44_chip_reset(bp, B44_CHIP_RESET_FULL);
	if (reset_kind == B44_FULL_RESET) {
		b44_phy_reset(bp);
		b44_setup_phy(bp);
	}

	/* Enable CRC32, set proper LED modes and power on PHY */
	bw32(bp, B44_MAC_CTRL, MAC_CTRL_CRC32_ENAB | MAC_CTRL_PHY_LEDCTRL);
	bw32(bp, B44_RCV_LAZY, (1 << RCV_LAZY_FC_SHIFT));

	/* This sets the MAC address too.  */
	__b44_set_rx_mode(bp->dev);

	/* MTU + eth header + possible VLAN tag + struct rx_header */
	bw32(bp, B44_RXMAXLEN, bp->dev->mtu + ETH_HLEN + 8 + RX_HEADER_LEN);
	bw32(bp, B44_TXMAXLEN, bp->dev->mtu + ETH_HLEN + 8 + RX_HEADER_LEN);

	bw32(bp, B44_TX_WMARK, 56); /* XXX magic */
	if (reset_kind == B44_PARTIAL_RESET) {
		bw32(bp, B44_DMARX_CTRL, (DMARX_CTRL_ENABLE |
				      (RX_PKT_OFFSET << DMARX_CTRL_ROSHIFT)));
	} else {
		bw32(bp, B44_DMATX_CTRL, DMATX_CTRL_ENABLE);
		bw32(bp, B44_DMATX_ADDR, bp->tx_ring_dma + bp->dma_offset);
		bw32(bp, B44_DMARX_CTRL, (DMARX_CTRL_ENABLE |
				      (RX_PKT_OFFSET << DMARX_CTRL_ROSHIFT)));
		bw32(bp, B44_DMARX_ADDR, bp->rx_ring_dma + bp->dma_offset);

		bw32(bp, B44_DMARX_PTR, bp->rx_pending);
		bp->rx_prod = bp->rx_pending;

		bw32(bp, B44_MIB_CTRL, MIB_CTRL_CLR_ON_READ);
	}

	val = br32(bp, B44_ENET_CTRL);
	bw32(bp, B44_ENET_CTRL, (val | ENET_CTRL_ENABLE));

	netdev_reset_queue(bp->dev);
}