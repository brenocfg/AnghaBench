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
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MVNETA_QSGMII_SERDES_PROTO ; 
 int /*<<< orphan*/  MVNETA_SERDES_CFG ; 
 int /*<<< orphan*/  MVNETA_SGMII_SERDES_PROTO ; 
 int /*<<< orphan*/  MVNETA_UNIT_INTR_CAUSE ; 
 int PHY_INTERFACE_MODE_QSGMII ; 
 int PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phy_interface_mode_is_8023z (int) ; 
 int /*<<< orphan*/  phy_interface_mode_is_rgmii (int) ; 

__attribute__((used)) static int mvneta_port_power_up(struct mvneta_port *pp, int phy_mode)
{
	/* MAC Cause register should be cleared */
	mvreg_write(pp, MVNETA_UNIT_INTR_CAUSE, 0);

	if (phy_mode == PHY_INTERFACE_MODE_QSGMII)
		mvreg_write(pp, MVNETA_SERDES_CFG, MVNETA_QSGMII_SERDES_PROTO);
	else if (phy_mode == PHY_INTERFACE_MODE_SGMII ||
		 phy_interface_mode_is_8023z(phy_mode))
		mvreg_write(pp, MVNETA_SERDES_CFG, MVNETA_SGMII_SERDES_PROTO);
	else if (!phy_interface_mode_is_rgmii(phy_mode))
		return -EINVAL;

	return 0;
}