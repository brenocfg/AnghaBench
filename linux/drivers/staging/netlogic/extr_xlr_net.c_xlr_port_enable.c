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
struct xlr_net_priv {int /*<<< orphan*/  base_addr; TYPE_1__* nd; } ;
struct TYPE_2__ {scalar_t__ phy_interface; } ;

/* Variables and functions */
 int O_MAC_CONFIG_1__rxen ; 
 int O_MAC_CONFIG_1__rxfc ; 
 int O_MAC_CONFIG_1__txen ; 
 int O_MAC_CONFIG_1__txfc ; 
 int O_RX_CONTROL__RGMII ; 
 int O_RX_CONTROL__RXENABLE ; 
 int O_TX_CONTROL__TXENABLE ; 
 int O_TX_CONTROL__TXTHRESHOLD ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  R_MAC_CONFIG_1 ; 
 int /*<<< orphan*/  R_RX_CONTROL ; 
 int /*<<< orphan*/  R_TX_CONTROL ; 
 int read_c0_prid () ; 
 int /*<<< orphan*/  xlr_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void xlr_port_enable(struct xlr_net_priv *priv)
{
	u32 prid = (read_c0_prid() & 0xf000);

	/* Setup MAC_CONFIG reg if (xls & rgmii) */
	if ((prid == 0x8000 || prid == 0x4000 || prid == 0xc000) &&
	    priv->nd->phy_interface == PHY_INTERFACE_MODE_RGMII)
		xlr_reg_update(priv->base_addr, R_RX_CONTROL,
			       (1 << O_RX_CONTROL__RGMII),
			       (1 << O_RX_CONTROL__RGMII));

	/* Rx Tx enable */
	xlr_reg_update(priv->base_addr, R_MAC_CONFIG_1,
		       ((1 << O_MAC_CONFIG_1__rxen) |
			(1 << O_MAC_CONFIG_1__txen) |
			(1 << O_MAC_CONFIG_1__rxfc) |
			(1 << O_MAC_CONFIG_1__txfc)),
		       ((1 << O_MAC_CONFIG_1__rxen) |
			(1 << O_MAC_CONFIG_1__txen) |
			(1 << O_MAC_CONFIG_1__rxfc) |
			(1 << O_MAC_CONFIG_1__txfc)));

	/* Setup tx control reg */
	xlr_reg_update(priv->base_addr, R_TX_CONTROL,
		       ((1 << O_TX_CONTROL__TXENABLE) |
		       (512 << O_TX_CONTROL__TXTHRESHOLD)), 0x3fff);

	/* Setup rx control reg */
	xlr_reg_update(priv->base_addr, R_RX_CONTROL,
		       1 << O_RX_CONTROL__RXENABLE,
		       1 << O_RX_CONTROL__RXENABLE);
}