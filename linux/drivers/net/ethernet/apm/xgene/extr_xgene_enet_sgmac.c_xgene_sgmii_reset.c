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
struct xgene_enet_pdata {scalar_t__ phy_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_PHY_ADDR ; 
 int LINK_UP ; 
 int SGMII_BASE_PAGE_ABILITY_ADDR ; 
 scalar_t__ SPEED_UNKNOWN ; 
 int xgene_mii_phy_read (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_sgmii_tbi_control_reset (struct xgene_enet_pdata*) ; 

__attribute__((used)) static void xgene_sgmii_reset(struct xgene_enet_pdata *p)
{
	u32 value;

	if (p->phy_speed == SPEED_UNKNOWN)
		return;

	value = xgene_mii_phy_read(p, INT_PHY_ADDR,
				   SGMII_BASE_PAGE_ABILITY_ADDR >> 2);
	if (!(value & LINK_UP))
		xgene_sgmii_tbi_control_reset(p);
}