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
typedef  enum hdmi_phy_type { ____Placeholder_hdmi_phy_type } hdmi_phy_type ;

/* Variables and functions */
#define  MSM_HDMI_PHY_8960 131 
#define  MSM_HDMI_PHY_8996 130 
#define  MSM_HDMI_PHY_8x60 129 
#define  MSM_HDMI_PHY_8x74 128 
 int msm_hdmi_pll_8960_init (struct platform_device*) ; 
 int msm_hdmi_pll_8996_init (struct platform_device*) ; 

__attribute__((used)) static int msm_hdmi_phy_pll_init(struct platform_device *pdev,
			     enum hdmi_phy_type type)
{
	int ret;

	switch (type) {
	case MSM_HDMI_PHY_8960:
		ret = msm_hdmi_pll_8960_init(pdev);
		break;
	case MSM_HDMI_PHY_8996:
		ret = msm_hdmi_pll_8996_init(pdev);
		break;
	/*
	 * we don't have PLL support for these, don't report an error for now
	 */
	case MSM_HDMI_PHY_8x60:
	case MSM_HDMI_PHY_8x74:
	default:
		ret = 0;
		break;
	}

	return ret;
}