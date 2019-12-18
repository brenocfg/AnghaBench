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
struct netdata_local {int /*<<< orphan*/  net_base; void* last_tx_idx; scalar_t__ num_used_tx_buffs; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENET_MAXF_SIZE ; 
 int LPC_CLRT_LOAD_COLLISION_WINDOW (int) ; 
 int LPC_CLRT_LOAD_RETRY_MAX (int) ; 
 int LPC_COMMAND_PASSRUNTFRAME ; 
 int LPC_COMMAND_RMII ; 
 int LPC_COMMAND_RXENABLE ; 
 int LPC_COMMAND_TXENABLE ; 
 int /*<<< orphan*/  LPC_ENET_CLRT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_COMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_INTCLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_IPGR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MAC1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MAC2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MAXF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_RXFILTER_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_SUPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_TXCONSUMEINDEX (int /*<<< orphan*/ ) ; 
 int LPC_IPGR_LOAD_PART2 (int) ; 
 int LPC_MAC1_PASS_ALL_RX_FRAMES ; 
 int LPC_MAC1_RECV_ENABLE ; 
 int LPC_MAC2_CRC_ENABLE ; 
 int LPC_MAC2_PAD_CRC_ENABLE ; 
 int LPC_RXFLTRW_ACCEPTPERFECT ; 
 int LPC_RXFLTRW_ACCEPTUBROADCAST ; 
 int LPC_SUPP_RESET_RMII ; 
 scalar_t__ PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  __lpc_params_setup (struct netdata_local*) ; 
 int /*<<< orphan*/  __lpc_txrx_desc_setup (struct netdata_local*) ; 
 int /*<<< orphan*/  lpc_eth_enable_int (int /*<<< orphan*/ ) ; 
 scalar_t__ lpc_phy_interface_mode (int /*<<< orphan*/ *) ; 
 void* readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __lpc_eth_init(struct netdata_local *pldat)
{
	u32 tmp;

	/* Disable controller and reset */
	tmp = readl(LPC_ENET_COMMAND(pldat->net_base));
	tmp &= ~LPC_COMMAND_RXENABLE | LPC_COMMAND_TXENABLE;
	writel(tmp, LPC_ENET_COMMAND(pldat->net_base));
	tmp = readl(LPC_ENET_MAC1(pldat->net_base));
	tmp &= ~LPC_MAC1_RECV_ENABLE;
	writel(tmp, LPC_ENET_MAC1(pldat->net_base));

	/* Initial MAC setup */
	writel(LPC_MAC1_PASS_ALL_RX_FRAMES, LPC_ENET_MAC1(pldat->net_base));
	writel((LPC_MAC2_PAD_CRC_ENABLE | LPC_MAC2_CRC_ENABLE),
	       LPC_ENET_MAC2(pldat->net_base));
	writel(ENET_MAXF_SIZE, LPC_ENET_MAXF(pldat->net_base));

	/* Collision window, gap */
	writel((LPC_CLRT_LOAD_RETRY_MAX(0xF) |
		LPC_CLRT_LOAD_COLLISION_WINDOW(0x37)),
	       LPC_ENET_CLRT(pldat->net_base));
	writel(LPC_IPGR_LOAD_PART2(0x12), LPC_ENET_IPGR(pldat->net_base));

	if (lpc_phy_interface_mode(&pldat->pdev->dev) == PHY_INTERFACE_MODE_MII)
		writel(LPC_COMMAND_PASSRUNTFRAME,
		       LPC_ENET_COMMAND(pldat->net_base));
	else {
		writel((LPC_COMMAND_PASSRUNTFRAME | LPC_COMMAND_RMII),
		       LPC_ENET_COMMAND(pldat->net_base));
		writel(LPC_SUPP_RESET_RMII, LPC_ENET_SUPP(pldat->net_base));
	}

	__lpc_params_setup(pldat);

	/* Setup TX and RX descriptors */
	__lpc_txrx_desc_setup(pldat);

	/* Setup packet filtering */
	writel((LPC_RXFLTRW_ACCEPTUBROADCAST | LPC_RXFLTRW_ACCEPTPERFECT),
	       LPC_ENET_RXFILTER_CTRL(pldat->net_base));

	/* Get the next TX buffer output index */
	pldat->num_used_tx_buffs = 0;
	pldat->last_tx_idx =
		readl(LPC_ENET_TXCONSUMEINDEX(pldat->net_base));

	/* Clear and enable interrupts */
	writel(0xFFFF, LPC_ENET_INTCLEAR(pldat->net_base));
	smp_wmb();
	lpc_eth_enable_int(pldat->net_base);

	/* Enable controller */
	tmp = readl(LPC_ENET_COMMAND(pldat->net_base));
	tmp |= LPC_COMMAND_RXENABLE | LPC_COMMAND_TXENABLE;
	writel(tmp, LPC_ENET_COMMAND(pldat->net_base));
	tmp = readl(LPC_ENET_MAC1(pldat->net_base));
	tmp |= LPC_MAC1_RECV_ENABLE;
	writel(tmp, LPC_ENET_MAC1(pldat->net_base));
}