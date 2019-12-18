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
typedef  int u16 ;
struct link_vars {int /*<<< orphan*/  link_status; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int /*<<< orphan*/  LINK_STATUS_PARALLEL_DETECTION_USED ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_STATUS ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void bnx2x_ext_phy_10G_an_resolve(struct bnx2x *bp,
				       struct bnx2x_phy *phy,
				       struct link_vars *vars)
{
	u16 val;
	bnx2x_cl45_read(bp, phy,
			MDIO_AN_DEVAD,
			MDIO_AN_REG_STATUS, &val);
	bnx2x_cl45_read(bp, phy,
			MDIO_AN_DEVAD,
			MDIO_AN_REG_STATUS, &val);
	if (val & (1<<5))
		vars->link_status |= LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;
	if ((val & (1<<0)) == 0)
		vars->link_status |= LINK_STATUS_PARALLEL_DETECTION_USED;
}