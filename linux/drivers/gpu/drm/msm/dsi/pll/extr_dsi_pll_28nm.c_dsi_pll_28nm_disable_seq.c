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
struct msm_dsi_pll {int dummy; } ;
struct dsi_pll_28nm {scalar_t__ mmio; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_DSI_28nm_PHY_PLL_GLB_CFG ; 
 int /*<<< orphan*/  pll_write (scalar_t__,int) ; 
 struct dsi_pll_28nm* to_pll_28nm (struct msm_dsi_pll*) ; 

__attribute__((used)) static void dsi_pll_28nm_disable_seq(struct msm_dsi_pll *pll)
{
	struct dsi_pll_28nm *pll_28nm = to_pll_28nm(pll);

	DBG("id=%d", pll_28nm->id);
	pll_write(pll_28nm->mmio + REG_DSI_28nm_PHY_PLL_GLB_CFG, 0x00);
}