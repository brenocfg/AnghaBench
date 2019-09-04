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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct bnx2x_reg_set {int member_1; int member_2; int reg; int val; int /*<<< orphan*/  const devad; int /*<<< orphan*/  const member_0; } ;
struct bnx2x_phy {scalar_t__ type; int /*<<< orphan*/  ver_addr; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bnx2x_reg_set*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  const MDIO_CTL_DEVAD ; 
#define  MDIO_PMA_DEVAD 128 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/  const,int,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/  const,int,int) ; 
 scalar_t__ bnx2x_is_8483x_8485x (struct bnx2x_phy*) ; 
 int /*<<< orphan*/  bnx2x_save_spirom_version (struct bnx2x*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bnx2x_save_848xx_spirom_version(struct bnx2x_phy *phy,
					    struct bnx2x *bp,
					    u8 port)
{
	u16 val, fw_ver2, cnt, i;
	static struct bnx2x_reg_set reg_set[] = {
		{MDIO_PMA_DEVAD, 0xA819, 0x0014},
		{MDIO_PMA_DEVAD, 0xA81A, 0xc200},
		{MDIO_PMA_DEVAD, 0xA81B, 0x0000},
		{MDIO_PMA_DEVAD, 0xA81C, 0x0300},
		{MDIO_PMA_DEVAD, 0xA817, 0x0009}
	};
	u16 fw_ver1;

	if (bnx2x_is_8483x_8485x(phy)) {
		bnx2x_cl45_read(bp, phy, MDIO_CTL_DEVAD, 0x400f, &fw_ver1);
		if (phy->type != PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858)
			fw_ver1 &= 0xfff;
		bnx2x_save_spirom_version(bp, port, fw_ver1, phy->ver_addr);
	} else {
		/* For 32-bit registers in 848xx, access via MDIO2ARM i/f. */
		/* (1) set reg 0xc200_0014(SPI_BRIDGE_CTRL_2) to 0x03000000 */
		for (i = 0; i < ARRAY_SIZE(reg_set); i++)
			bnx2x_cl45_write(bp, phy, reg_set[i].devad,
					 reg_set[i].reg, reg_set[i].val);

		for (cnt = 0; cnt < 100; cnt++) {
			bnx2x_cl45_read(bp, phy, MDIO_PMA_DEVAD, 0xA818, &val);
			if (val & 1)
				break;
			udelay(5);
		}
		if (cnt == 100) {
			DP(NETIF_MSG_LINK, "Unable to read 848xx "
					"phy fw version(1)\n");
			bnx2x_save_spirom_version(bp, port, 0,
						  phy->ver_addr);
			return;
		}


		/* 2) read register 0xc200_0000 (SPI_FW_STATUS) */
		bnx2x_cl45_write(bp, phy, MDIO_PMA_DEVAD, 0xA819, 0x0000);
		bnx2x_cl45_write(bp, phy, MDIO_PMA_DEVAD, 0xA81A, 0xc200);
		bnx2x_cl45_write(bp, phy, MDIO_PMA_DEVAD, 0xA817, 0x000A);
		for (cnt = 0; cnt < 100; cnt++) {
			bnx2x_cl45_read(bp, phy, MDIO_PMA_DEVAD, 0xA818, &val);
			if (val & 1)
				break;
			udelay(5);
		}
		if (cnt == 100) {
			DP(NETIF_MSG_LINK, "Unable to read 848xx phy fw "
					"version(2)\n");
			bnx2x_save_spirom_version(bp, port, 0,
						  phy->ver_addr);
			return;
		}

		/* lower 16 bits of the register SPI_FW_STATUS */
		bnx2x_cl45_read(bp, phy, MDIO_PMA_DEVAD, 0xA81B, &fw_ver1);
		/* upper 16 bits of register SPI_FW_STATUS */
		bnx2x_cl45_read(bp, phy, MDIO_PMA_DEVAD, 0xA81C, &fw_ver2);

		bnx2x_save_spirom_version(bp, port, (fw_ver2<<16) | fw_ver1,
					  phy->ver_addr);
	}

}