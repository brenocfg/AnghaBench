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
typedef  int u16 ;
struct sky2_port {unsigned int port; int /*<<< orphan*/  tx_prod; int /*<<< orphan*/  phy_lock; struct sky2_hw* hw; } ;
struct sky2_hw {scalar_t__ chip_id; scalar_t__ chip_rev; scalar_t__* dev; } ;

/* Variables and functions */
 int BMU_STOP ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMC_PAUSE_OFF ; 
 int /*<<< orphan*/  GMC_RST_SET ; 
 int /*<<< orphan*/  GMF_RST_SET ; 
 int GM_GPCR_RX_ENA ; 
 int GM_GPCR_TX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  GPC_RST_SET ; 
 int /*<<< orphan*/  GPHY_CTRL ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 int /*<<< orphan*/  RB_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 int RB_DIS_OP_MD ; 
 int RB_RST_SET ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAT_ISR_TIMER_CNT ; 
 int /*<<< orphan*/  STAT_ISR_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_LEV_TIMER_CNT ; 
 int /*<<< orphan*/  STAT_TX_TIMER_CNT ; 
 int gma_read16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_running (scalar_t__) ; 
 int /*<<< orphan*/  sky2_phy_power_down (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_read8 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_rx_stop (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_tx_complete (struct sky2_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_tx_reset (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * txqaddr ; 

__attribute__((used)) static void sky2_hw_down(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	u16 ctrl;

	/* Force flow control off */
	sky2_write8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);

	/* Stop transmitter */
	sky2_write32(hw, Q_ADDR(txqaddr[port], Q_CSR), BMU_STOP);
	sky2_read32(hw, Q_ADDR(txqaddr[port], Q_CSR));

	sky2_write32(hw, RB_ADDR(txqaddr[port], RB_CTRL),
		     RB_RST_SET | RB_DIS_OP_MD);

	ctrl = gma_read16(hw, port, GM_GP_CTRL);
	ctrl &= ~(GM_GPCR_TX_ENA | GM_GPCR_RX_ENA);
	gma_write16(hw, port, GM_GP_CTRL, ctrl);

	sky2_write8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_SET);

	/* Workaround shared GMAC reset */
	if (!(hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev == 0 &&
	      port == 0 && hw->dev[1] && netif_running(hw->dev[1])))
		sky2_write8(hw, SK_REG(port, GMAC_CTRL), GMC_RST_SET);

	sky2_write8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_SET);

	/* Force any delayed status interrupt and NAPI */
	sky2_write32(hw, STAT_LEV_TIMER_CNT, 0);
	sky2_write32(hw, STAT_TX_TIMER_CNT, 0);
	sky2_write32(hw, STAT_ISR_TIMER_CNT, 0);
	sky2_read8(hw, STAT_ISR_TIMER_CTRL);

	sky2_rx_stop(sky2);

	spin_lock_bh(&sky2->phy_lock);
	sky2_phy_power_down(hw, port);
	spin_unlock_bh(&sky2->phy_lock);

	sky2_tx_reset(hw, port);

	/* Free any pending frames stuck in HW queue */
	sky2_tx_complete(sky2, sky2->tx_prod);
}