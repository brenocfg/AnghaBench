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
struct phylink_link_state {int an_complete; int link; int duplex; int /*<<< orphan*/  pause; void* speed; } ;
struct mvpp2_port {int phy_interface; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLO_PAUSE_RX ; 
 int /*<<< orphan*/  MLO_PAUSE_TX ; 
 scalar_t__ MVPP2_GMAC_STATUS0 ; 
 int MVPP2_GMAC_STATUS0_AN_COMPLETE ; 
 int MVPP2_GMAC_STATUS0_FULL_DUPLEX ; 
 int MVPP2_GMAC_STATUS0_GMII_SPEED ; 
 int MVPP2_GMAC_STATUS0_LINK_UP ; 
 int MVPP2_GMAC_STATUS0_MII_SPEED ; 
 int MVPP2_GMAC_STATUS0_RX_PAUSE ; 
 int MVPP2_GMAC_STATUS0_TX_PAUSE ; 
#define  PHY_INTERFACE_MODE_1000BASEX 129 
#define  PHY_INTERFACE_MODE_2500BASEX 128 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 void* SPEED_2500 ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void mvpp2_gmac_link_state(struct mvpp2_port *port,
				  struct phylink_link_state *state)
{
	u32 val;

	val = readl(port->base + MVPP2_GMAC_STATUS0);

	state->an_complete = !!(val & MVPP2_GMAC_STATUS0_AN_COMPLETE);
	state->link = !!(val & MVPP2_GMAC_STATUS0_LINK_UP);
	state->duplex = !!(val & MVPP2_GMAC_STATUS0_FULL_DUPLEX);

	switch (port->phy_interface) {
	case PHY_INTERFACE_MODE_1000BASEX:
		state->speed = SPEED_1000;
		break;
	case PHY_INTERFACE_MODE_2500BASEX:
		state->speed = SPEED_2500;
		break;
	default:
		if (val & MVPP2_GMAC_STATUS0_GMII_SPEED)
			state->speed = SPEED_1000;
		else if (val & MVPP2_GMAC_STATUS0_MII_SPEED)
			state->speed = SPEED_100;
		else
			state->speed = SPEED_10;
	}

	state->pause = 0;
	if (val & MVPP2_GMAC_STATUS0_RX_PAUSE)
		state->pause |= MLO_PAUSE_RX;
	if (val & MVPP2_GMAC_STATUS0_TX_PAUSE)
		state->pause |= MLO_PAUSE_TX;
}