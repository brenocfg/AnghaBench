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
struct mii_phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ phy_read (struct mii_phy*,int) ; 
 int /*<<< orphan*/  phy_write (struct mii_phy*,int,int) ; 

__attribute__((used)) static int et1011c_init(struct mii_phy *phy)
{
	u16 reg_short;

	reg_short = (u16)(phy_read(phy, 0x16));
	reg_short &= ~(0x7);
	reg_short |= 0x6;	/* RGMII Trace Delay*/
	phy_write(phy, 0x16, reg_short);

	reg_short = (u16)(phy_read(phy, 0x17));
	reg_short &= ~(0x40);
	phy_write(phy, 0x17, reg_short);

	phy_write(phy, 0x1c, 0x74f0);
	return 0;
}