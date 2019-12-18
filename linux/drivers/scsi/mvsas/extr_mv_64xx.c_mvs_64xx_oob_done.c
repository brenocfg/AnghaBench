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
 int /*<<< orphan*/  PHYR_PHY_STAT ; 
 int PHY_OOB_DTCTD ; 
 int mvs_read_port_cfg_data (struct mvs_info*,int) ; 
 int /*<<< orphan*/  mvs_write_port_cfg_addr (struct mvs_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvs_64xx_oob_done(struct mvs_info *mvi, int i)
{
	u32 phy_st;
	mvs_write_port_cfg_addr(mvi, i,
			PHYR_PHY_STAT);
	phy_st = mvs_read_port_cfg_data(mvi, i);
	if (phy_st & PHY_OOB_DTCTD)
		return 1;
	return 0;
}