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
struct msm_dsi_pll {int (* set_usecase ) (struct msm_dsi_pll*,int) ;} ;
typedef  enum msm_dsi_phy_usecase { ____Placeholder_msm_dsi_phy_usecase } msm_dsi_phy_usecase ;

/* Variables and functions */
 int stub1 (struct msm_dsi_pll*,int) ; 

int msm_dsi_pll_set_usecase(struct msm_dsi_pll *pll,
			    enum msm_dsi_phy_usecase uc)
{
	if (pll->set_usecase)
		return pll->set_usecase(pll, uc);

	return 0;
}