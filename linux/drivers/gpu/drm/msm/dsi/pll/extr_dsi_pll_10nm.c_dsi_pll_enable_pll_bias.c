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
struct dsi_pll_10nm {scalar_t__ mmio; scalar_t__ phy_cmn_mmio; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ REG_DSI_10nm_PHY_CMN_CTRL_0 ; 
 scalar_t__ REG_DSI_10nm_PHY_PLL_SYSTEM_MUXES ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int pll_read (scalar_t__) ; 
 int /*<<< orphan*/  pll_write (scalar_t__,int) ; 

__attribute__((used)) static void dsi_pll_enable_pll_bias(struct dsi_pll_10nm *pll)
{
	u32 data = pll_read(pll->phy_cmn_mmio + REG_DSI_10nm_PHY_CMN_CTRL_0);

	pll_write(pll->phy_cmn_mmio + REG_DSI_10nm_PHY_CMN_CTRL_0,
		  data | BIT(5));
	pll_write(pll->mmio + REG_DSI_10nm_PHY_PLL_SYSTEM_MUXES, 0xc0);
	ndelay(250);
}