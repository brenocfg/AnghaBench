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
struct skge_port {int port; scalar_t__ duplex; scalar_t__ autoneg; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  GMAC_DEF_MSK ; 
 int /*<<< orphan*/  GMAC_IRQ_MSK ; 
 int GM_GPCR_DUP_FULL ; 
 int GM_GPCR_RX_ENA ; 
 int GM_GPCR_TX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  PHY_MARV_INT_MASK ; 
 int /*<<< orphan*/  PHY_M_IS_DEF_MSK ; 
 int /*<<< orphan*/  SK_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gma_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_link_up (struct skge_port*) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yukon_link_up(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	u16 reg;

	/* Enable Transmit FIFO Underrun */
	skge_write8(hw, SK_REG(port, GMAC_IRQ_MSK), GMAC_DEF_MSK);

	reg = gma_read16(hw, port, GM_GP_CTRL);
	if (skge->duplex == DUPLEX_FULL || skge->autoneg == AUTONEG_ENABLE)
		reg |= GM_GPCR_DUP_FULL;

	/* enable Rx/Tx */
	reg |= GM_GPCR_RX_ENA | GM_GPCR_TX_ENA;
	gma_write16(hw, port, GM_GP_CTRL, reg);

	gm_phy_write(hw, port, PHY_MARV_INT_MASK, PHY_M_IS_DEF_MSK);
	skge_link_up(skge);
}