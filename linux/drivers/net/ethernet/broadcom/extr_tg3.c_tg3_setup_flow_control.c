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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ autoneg; scalar_t__ flowctrl; scalar_t__ active_flowctrl; } ;
struct tg3 {int phy_flags; int /*<<< orphan*/  tx_mode; int /*<<< orphan*/  rx_mode; TYPE_1__ link_config; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  mdio_bus; } ;
struct TYPE_4__ {scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ FLOW_CTRL_RX ; 
 scalar_t__ FLOW_CTRL_TX ; 
 int /*<<< orphan*/  MAC_RX_MODE ; 
 int /*<<< orphan*/  MAC_TX_MODE ; 
 int /*<<< orphan*/  PAUSE_AUTONEG ; 
 int /*<<< orphan*/  RX_MODE_FLOW_CTRL_ENABLE ; 
 int TG3_PHYFLG_ANY_SERDES ; 
 int /*<<< orphan*/  TX_MODE_FLOW_CTRL_ENABLE ; 
 int /*<<< orphan*/  USE_PHYLIB ; 
 TYPE_2__* mdiobus_get_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_resolve_flowctrl_1000X (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_setup_flow_control(struct tg3 *tp, u32 lcladv, u32 rmtadv)
{
	u8 autoneg;
	u8 flowctrl = 0;
	u32 old_rx_mode = tp->rx_mode;
	u32 old_tx_mode = tp->tx_mode;

	if (tg3_flag(tp, USE_PHYLIB))
		autoneg = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr)->autoneg;
	else
		autoneg = tp->link_config.autoneg;

	if (autoneg == AUTONEG_ENABLE && tg3_flag(tp, PAUSE_AUTONEG)) {
		if (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
			flowctrl = tg3_resolve_flowctrl_1000X(lcladv, rmtadv);
		else
			flowctrl = mii_resolve_flowctrl_fdx(lcladv, rmtadv);
	} else
		flowctrl = tp->link_config.flowctrl;

	tp->link_config.active_flowctrl = flowctrl;

	if (flowctrl & FLOW_CTRL_RX)
		tp->rx_mode |= RX_MODE_FLOW_CTRL_ENABLE;
	else
		tp->rx_mode &= ~RX_MODE_FLOW_CTRL_ENABLE;

	if (old_rx_mode != tp->rx_mode)
		tw32_f(MAC_RX_MODE, tp->rx_mode);

	if (flowctrl & FLOW_CTRL_TX)
		tp->tx_mode |= TX_MODE_FLOW_CTRL_ENABLE;
	else
		tp->tx_mode &= ~TX_MODE_FLOW_CTRL_ENABLE;

	if (old_tx_mode != tp->tx_mode)
		tw32_f(MAC_TX_MODE, tp->tx_mode);
}