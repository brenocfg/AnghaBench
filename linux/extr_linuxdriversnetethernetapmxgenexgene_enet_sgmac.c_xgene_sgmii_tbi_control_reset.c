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
struct xgene_enet_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_PHY_ADDR ; 
 int SGMII_TBI_CONTROL_ADDR ; 
 int /*<<< orphan*/  xgene_mii_phy_write (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void xgene_sgmii_tbi_control_reset(struct xgene_enet_pdata *p)
{
	xgene_mii_phy_write(p, INT_PHY_ADDR, SGMII_TBI_CONTROL_ADDR >> 2,
			    0x8000);
	xgene_mii_phy_write(p, INT_PHY_ADDR, SGMII_TBI_CONTROL_ADDR >> 2, 0);
}