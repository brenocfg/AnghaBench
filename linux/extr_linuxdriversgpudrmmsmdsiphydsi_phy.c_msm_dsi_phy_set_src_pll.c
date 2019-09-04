#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct msm_dsi_phy {int id; int base; TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__** src_pll_truthtable; } ;

/* Variables and functions */
 int DSI_MAX ; 
 int dsi_phy_read (int) ; 
 int /*<<< orphan*/  dsi_phy_write (int,int) ; 

void msm_dsi_phy_set_src_pll(struct msm_dsi_phy *phy, int pll_id, u32 reg,
				u32 bit_mask)
{
	int phy_id = phy->id;
	u32 val;

	if ((phy_id >= DSI_MAX) || (pll_id >= DSI_MAX))
		return;

	val = dsi_phy_read(phy->base + reg);

	if (phy->cfg->src_pll_truthtable[phy_id][pll_id])
		dsi_phy_write(phy->base + reg, val | bit_mask);
	else
		dsi_phy_write(phy->base + reg, val & (~bit_mask));
}