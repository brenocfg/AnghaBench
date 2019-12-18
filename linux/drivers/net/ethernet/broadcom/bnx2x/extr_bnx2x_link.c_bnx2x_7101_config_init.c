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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct link_vars {int dummy; } ;
struct link_params {int /*<<< orphan*/  port; struct bnx2x* bp; } ;
struct bnx2x_phy {int /*<<< orphan*/  ver_addr; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_REG_7101_VER1 ; 
 int /*<<< orphan*/  MDIO_PMA_REG_7101_VER2 ; 
 int /*<<< orphan*/  MDIO_PMA_REG_7107_LED_CNTL ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_2 ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_OUTPUT_HIGH ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_ext_phy_hw_reset (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_ext_phy_set_pause (struct link_params*,struct bnx2x_phy*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_save_spirom_version (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_gpio (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_wait_reset_complete (struct bnx2x*,struct bnx2x_phy*,struct link_params*) ; 

__attribute__((used)) static int bnx2x_7101_config_init(struct bnx2x_phy *phy,
				  struct link_params *params,
				  struct link_vars *vars)
{
	u16 fw_ver1, fw_ver2, val;
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Setting the SFX7101 LASI indication\n");

	/* Restore normal power mode*/
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_HIGH, params->port);
	/* HW reset */
	bnx2x_ext_phy_hw_reset(bp, params->port);
	bnx2x_wait_reset_complete(bp, phy, params);

	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0x1);
	DP(NETIF_MSG_LINK, "Setting the SFX7101 LED to blink on traffic\n");
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_7107_LED_CNTL, (1<<3));

	bnx2x_ext_phy_set_pause(params, phy, vars);
	/* Restart autoneg */
	bnx2x_cl45_read(bp, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, &val);
	val |= 0x200;
	bnx2x_cl45_write(bp, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, val);

	/* Save spirom version */
	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_7101_VER1, &fw_ver1);

	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_7101_VER2, &fw_ver2);
	bnx2x_save_spirom_version(bp, params->port,
				  (u32)(fw_ver1<<16 | fw_ver2), phy->ver_addr);
	return 0;
}