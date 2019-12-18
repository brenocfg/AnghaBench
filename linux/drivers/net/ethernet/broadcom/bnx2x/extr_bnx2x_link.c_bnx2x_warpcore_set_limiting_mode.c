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
typedef  int u8 ;
typedef  int u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
#define  EDC_MODE_ACTIVE_DAC 131 
#define  EDC_MODE_LIMITING 130 
#define  EDC_MODE_LINEAR 129 
#define  EDC_MODE_PASSIVE_DAC 128 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE ; 
 int MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_DEFAULT ; 
 int MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_SFP_DAC ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bnx2x_get_warpcore_lane (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_warpcore_reset_lane (struct bnx2x*,struct bnx2x_phy*,int) ; 

__attribute__((used)) static void bnx2x_warpcore_set_limiting_mode(struct link_params *params,
					     struct bnx2x_phy *phy,
					     u16 edc_mode)
{
	u16 val = 0;
	u16 mode = MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_DEFAULT;
	struct bnx2x *bp = params->bp;

	u8 lane = bnx2x_get_warpcore_lane(phy, params);
	/* This is a global register which controls all lanes */
	bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE, &val);
	val &= ~(0xf << (lane << 2));

	switch (edc_mode) {
	case EDC_MODE_LINEAR:
	case EDC_MODE_LIMITING:
		mode = MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_DEFAULT;
		break;
	case EDC_MODE_PASSIVE_DAC:
	case EDC_MODE_ACTIVE_DAC:
		mode = MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_SFP_DAC;
		break;
	default:
		break;
	}

	val |= (mode << (lane << 2));
	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE, val);
	/* A must read */
	bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE, &val);

	/* Restart microcode to re-read the new mode */
	bnx2x_warpcore_reset_lane(bp, phy, 1);
	bnx2x_warpcore_reset_lane(bp, phy, 0);

}