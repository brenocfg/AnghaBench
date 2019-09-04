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
struct dsi_pll_10nm {scalar_t__ phy_cmn_mmio; } ;

/* Variables and functions */
 scalar_t__ REG_DSI_10nm_PHY_CMN_RBUF_CTRL ; 
 int /*<<< orphan*/  dsi_pll_disable_pll_bias (struct dsi_pll_10nm*) ; 
 int /*<<< orphan*/  pll_write (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_pll_disable_sub(struct dsi_pll_10nm *pll)
{
	pll_write(pll->phy_cmn_mmio + REG_DSI_10nm_PHY_CMN_RBUF_CTRL, 0);
	dsi_pll_disable_pll_bias(pll);
}