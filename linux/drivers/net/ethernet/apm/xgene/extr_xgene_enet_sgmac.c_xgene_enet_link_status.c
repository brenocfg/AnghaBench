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
struct xgene_enet_pdata {int /*<<< orphan*/  phy_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_PHY_ADDR ; 
 scalar_t__ LINK_SPEED (int) ; 
 int LINK_UP ; 
 scalar_t__ PHY_SPEED_100 ; 
 scalar_t__ PHY_SPEED_1000 ; 
 int SGMII_BASE_PAGE_ABILITY_ADDR ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int xgene_mii_phy_read (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 xgene_enet_link_status(struct xgene_enet_pdata *p)
{
	u32 data;

	data = xgene_mii_phy_read(p, INT_PHY_ADDR,
				  SGMII_BASE_PAGE_ABILITY_ADDR >> 2);

	if (LINK_SPEED(data) == PHY_SPEED_1000)
		p->phy_speed = SPEED_1000;
	else if (LINK_SPEED(data) == PHY_SPEED_100)
		p->phy_speed = SPEED_100;
	else
		p->phy_speed = SPEED_10;

	return data & LINK_UP;
}