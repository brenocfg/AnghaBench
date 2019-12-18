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
typedef  int u32 ;
struct phylink_link_state {int pause; } ;
struct mvpp2_port {scalar_t__ base; } ;

/* Variables and functions */
 int MLO_PAUSE_RX ; 
 int MLO_PAUSE_TX ; 
 int MVPP22_XLG_CTRL0_MAC_RESET_DIS ; 
 scalar_t__ MVPP22_XLG_CTRL0_REG ; 
 int MVPP22_XLG_CTRL0_RX_FLOW_CTRL_EN ; 
 int MVPP22_XLG_CTRL0_TX_FLOW_CTRL_EN ; 
 int MVPP22_XLG_CTRL4_EN_IDLE_CHECK ; 
 int MVPP22_XLG_CTRL4_FWD_FC ; 
 int MVPP22_XLG_CTRL4_FWD_PFC ; 
 int MVPP22_XLG_CTRL4_MACMODSELECT_GMAC ; 
 scalar_t__ MVPP22_XLG_CTRL4_REG ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mvpp2_xlg_config(struct mvpp2_port *port, unsigned int mode,
			     const struct phylink_link_state *state)
{
	u32 old_ctrl0, ctrl0;
	u32 old_ctrl4, ctrl4;

	old_ctrl0 = ctrl0 = readl(port->base + MVPP22_XLG_CTRL0_REG);
	old_ctrl4 = ctrl4 = readl(port->base + MVPP22_XLG_CTRL4_REG);

	ctrl0 |= MVPP22_XLG_CTRL0_MAC_RESET_DIS;

	if (state->pause & MLO_PAUSE_TX)
		ctrl0 |= MVPP22_XLG_CTRL0_TX_FLOW_CTRL_EN;
	else
		ctrl0 &= ~MVPP22_XLG_CTRL0_TX_FLOW_CTRL_EN;

	if (state->pause & MLO_PAUSE_RX)
		ctrl0 |= MVPP22_XLG_CTRL0_RX_FLOW_CTRL_EN;
	else
		ctrl0 &= ~MVPP22_XLG_CTRL0_RX_FLOW_CTRL_EN;

	ctrl4 &= ~(MVPP22_XLG_CTRL4_MACMODSELECT_GMAC |
		   MVPP22_XLG_CTRL4_EN_IDLE_CHECK);
	ctrl4 |= MVPP22_XLG_CTRL4_FWD_FC | MVPP22_XLG_CTRL4_FWD_PFC;

	if (old_ctrl0 != ctrl0)
		writel(ctrl0, port->base + MVPP22_XLG_CTRL0_REG);
	if (old_ctrl4 != ctrl4)
		writel(ctrl4, port->base + MVPP22_XLG_CTRL4_REG);

	if (!(old_ctrl0 & MVPP22_XLG_CTRL0_MAC_RESET_DIS)) {
		while (!(readl(port->base + MVPP22_XLG_CTRL0_REG) &
			 MVPP22_XLG_CTRL0_MAC_RESET_DIS))
			continue;
	}
}