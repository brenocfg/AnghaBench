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
typedef  unsigned int u32 ;
struct net_device {unsigned int mtu; int /*<<< orphan*/  dev_addr; } ;
struct emac_adapter {unsigned int rxbuf_size; scalar_t__ base; struct net_device* netdev; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 unsigned int DATA_BYTE_SWAP ; 
 scalar_t__ EMAC_AXI_MAST_CTRL ; 
 scalar_t__ EMAC_CLK_GATE_CTRL ; 
 unsigned int EMAC_DEF_RX_BUF_SIZE ; 
 scalar_t__ EMAC_MAX_FRAM_LEN_CTRL ; 
 scalar_t__ EMAC_MISC_CTRL ; 
 unsigned int ETH_FCS_LEN ; 
 unsigned int ETH_HLEN ; 
 unsigned int MAX_BOUND ; 
 unsigned int MAX_BTYPE ; 
 unsigned int RX_UNCPL_INT_EN ; 
 unsigned int VLAN_HLEN ; 
 int /*<<< orphan*/  emac_mac_dma_config (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_mac_dma_rings_config (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_mac_rx_config (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_mac_tx_config (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_set_mac_address (struct emac_adapter*,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void emac_mac_config(struct emac_adapter *adpt)
{
	struct net_device *netdev = adpt->netdev;
	unsigned int max_frame;
	u32 val;

	emac_set_mac_address(adpt, netdev->dev_addr);

	max_frame = netdev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	adpt->rxbuf_size = netdev->mtu > EMAC_DEF_RX_BUF_SIZE ?
		ALIGN(max_frame, 8) : EMAC_DEF_RX_BUF_SIZE;

	emac_mac_dma_rings_config(adpt);

	writel(netdev->mtu + ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN,
	       adpt->base + EMAC_MAX_FRAM_LEN_CTRL);

	emac_mac_tx_config(adpt);
	emac_mac_rx_config(adpt);
	emac_mac_dma_config(adpt);

	val = readl(adpt->base + EMAC_AXI_MAST_CTRL);
	val &= ~(DATA_BYTE_SWAP | MAX_BOUND);
	val |= MAX_BTYPE;
	writel(val, adpt->base + EMAC_AXI_MAST_CTRL);
	writel(0, adpt->base + EMAC_CLK_GATE_CTRL);
	writel(RX_UNCPL_INT_EN, adpt->base + EMAC_MISC_CTRL);
}