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
struct dsi_pll_10nm {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 struct dsi_pll_10nm* to_pll_10nm (struct msm_dsi_pll*) ; 

__attribute__((used)) static void dsi_pll_10nm_destroy(struct msm_dsi_pll *pll)
{
	struct dsi_pll_10nm *pll_10nm = to_pll_10nm(pll);

	DBG("DSI PLL%d", pll_10nm->id);
}