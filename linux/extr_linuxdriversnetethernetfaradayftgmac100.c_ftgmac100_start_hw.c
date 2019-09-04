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
typedef  int u32 ;
struct ftgmac100 {scalar_t__ cur_duplex; scalar_t__ base; TYPE_1__* netdev; } ;
struct TYPE_2__ {int flags; int features; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int FTGMAC100_MACCR_CRC_APD ; 
 int FTGMAC100_MACCR_FAST_MODE ; 
 int FTGMAC100_MACCR_FULLDUP ; 
 int FTGMAC100_MACCR_GIGA_MODE ; 
 int FTGMAC100_MACCR_HT_MULTI_EN ; 
 int FTGMAC100_MACCR_PHY_LINK_LEVEL ; 
 int FTGMAC100_MACCR_RM_VLAN ; 
 int FTGMAC100_MACCR_RXDMA_EN ; 
 int FTGMAC100_MACCR_RXMAC_EN ; 
 int FTGMAC100_MACCR_RX_ALL ; 
 int FTGMAC100_MACCR_RX_BROADPKT ; 
 int FTGMAC100_MACCR_RX_MULTIPKT ; 
 int FTGMAC100_MACCR_RX_RUNT ; 
 int FTGMAC100_MACCR_TXDMA_EN ; 
 int FTGMAC100_MACCR_TXMAC_EN ; 
 scalar_t__ FTGMAC100_OFFSET_MACCR ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 scalar_t__ netdev_mc_count (TYPE_1__*) ; 

__attribute__((used)) static void ftgmac100_start_hw(struct ftgmac100 *priv)
{
	u32 maccr = ioread32(priv->base + FTGMAC100_OFFSET_MACCR);

	/* Keep the original GMAC and FAST bits */
	maccr &= (FTGMAC100_MACCR_FAST_MODE | FTGMAC100_MACCR_GIGA_MODE);

	/* Add all the main enable bits */
	maccr |= FTGMAC100_MACCR_TXDMA_EN	|
		 FTGMAC100_MACCR_RXDMA_EN	|
		 FTGMAC100_MACCR_TXMAC_EN	|
		 FTGMAC100_MACCR_RXMAC_EN	|
		 FTGMAC100_MACCR_CRC_APD	|
		 FTGMAC100_MACCR_PHY_LINK_LEVEL	|
		 FTGMAC100_MACCR_RX_RUNT	|
		 FTGMAC100_MACCR_RX_BROADPKT;

	/* Add other bits as needed */
	if (priv->cur_duplex == DUPLEX_FULL)
		maccr |= FTGMAC100_MACCR_FULLDUP;
	if (priv->netdev->flags & IFF_PROMISC)
		maccr |= FTGMAC100_MACCR_RX_ALL;
	if (priv->netdev->flags & IFF_ALLMULTI)
		maccr |= FTGMAC100_MACCR_RX_MULTIPKT;
	else if (netdev_mc_count(priv->netdev))
		maccr |= FTGMAC100_MACCR_HT_MULTI_EN;

	/* Vlan filtering enabled */
	if (priv->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		maccr |= FTGMAC100_MACCR_RM_VLAN;

	/* Hit the HW */
	iowrite32(maccr, priv->base + FTGMAC100_OFFSET_MACCR);
}