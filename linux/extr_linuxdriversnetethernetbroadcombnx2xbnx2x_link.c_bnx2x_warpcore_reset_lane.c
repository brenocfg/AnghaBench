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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_DIGITAL5_MISC6 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_warpcore_reset_lane(struct bnx2x *bp,
				      struct bnx2x_phy *phy,
				      u8 reset)
{
	u16 val;
	/* Take lane out of reset after configuration is finished */
	bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_DIGITAL5_MISC6, &val);
	if (reset)
		val |= 0xC000;
	else
		val &= 0x3FFF;
	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_DIGITAL5_MISC6, val);
	bnx2x_cl45_read(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_DIGITAL5_MISC6, &val);
}