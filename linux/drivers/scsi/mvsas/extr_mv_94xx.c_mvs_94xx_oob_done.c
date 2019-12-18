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
struct mvs_info {int dummy; } ;

/* Variables and functions */
 int PHY_READY_MASK ; 
 int mvs_read_phy_ctl (struct mvs_info*,int) ; 

__attribute__((used)) static int mvs_94xx_oob_done(struct mvs_info *mvi, int i)
{
	u32 phy_st;
	phy_st = mvs_read_phy_ctl(mvi, i);
	if (phy_st & PHY_READY_MASK)
		return 1;
	return 0;
}