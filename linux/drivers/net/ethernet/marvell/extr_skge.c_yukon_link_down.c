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
struct skge_port {int port; scalar_t__ flow_status; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ FLOW_STAT_REM_SEND ; 
 int GM_GPCR_RX_ENA ; 
 int GM_GPCR_TX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  PHY_MARV_AUNE_ADV ; 
 int PHY_M_AN_ASP ; 
 int gm_phy_read (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int gma_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_link_down (struct skge_port*) ; 
 int /*<<< orphan*/  yukon_init (struct skge_hw*,int) ; 

__attribute__((used)) static void yukon_link_down(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	u16 ctrl;

	ctrl = gma_read16(hw, port, GM_GP_CTRL);
	ctrl &= ~(GM_GPCR_RX_ENA | GM_GPCR_TX_ENA);
	gma_write16(hw, port, GM_GP_CTRL, ctrl);

	if (skge->flow_status == FLOW_STAT_REM_SEND) {
		ctrl = gm_phy_read(hw, port, PHY_MARV_AUNE_ADV);
		ctrl |= PHY_M_AN_ASP;
		/* restore Asymmetric Pause bit */
		gm_phy_write(hw, port, PHY_MARV_AUNE_ADV, ctrl);
	}

	skge_link_down(skge);

	yukon_init(hw, port);
}