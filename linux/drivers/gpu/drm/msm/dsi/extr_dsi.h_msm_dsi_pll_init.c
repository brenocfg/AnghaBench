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
struct platform_device {int dummy; } ;
struct msm_dsi_pll {int dummy; } ;
typedef  enum msm_dsi_phy_type { ____Placeholder_msm_dsi_phy_type } msm_dsi_phy_type ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct msm_dsi_pll* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct msm_dsi_pll *msm_dsi_pll_init(struct platform_device *pdev,
			 enum msm_dsi_phy_type type, int id) {
	return ERR_PTR(-ENODEV);
}