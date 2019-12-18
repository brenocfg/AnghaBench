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
struct msm_dsi_phy {int /*<<< orphan*/ * pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_dsi_pll_destroy (int /*<<< orphan*/ *) ; 
 struct msm_dsi_phy* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsi_phy_driver_remove(struct platform_device *pdev)
{
	struct msm_dsi_phy *phy = platform_get_drvdata(pdev);

	if (phy && phy->pll) {
		msm_dsi_pll_destroy(phy->pll);
		phy->pll = NULL;
	}

	platform_set_drvdata(pdev, NULL);

	return 0;
}