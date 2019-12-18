#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ phy_type; scalar_t__ ulpi_fs_ls; } ;
struct TYPE_3__ {scalar_t__ hs_phy_type; scalar_t__ fs_phy_type; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; TYPE_2__ params; TYPE_1__ hw_params; } ;

/* Variables and functions */
 scalar_t__ DWC2_PHY_TYPE_PARAM_FS ; 
 scalar_t__ GHWCFG2_FS_PHY_TYPE_DEDICATED ; 
 scalar_t__ GHWCFG2_HS_PHY_TYPE_ULPI ; 
 int /*<<< orphan*/  HCFG ; 
 int HCFG_FSLSPCLKSEL_30_60_MHZ ; 
 int HCFG_FSLSPCLKSEL_48_MHZ ; 
 int HCFG_FSLSPCLKSEL_MASK ; 
 int HCFG_FSLSPCLKSEL_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

void dwc2_init_fs_ls_pclk_sel(struct dwc2_hsotg *hsotg)
{
	u32 hcfg, val;

	if ((hsotg->hw_params.hs_phy_type == GHWCFG2_HS_PHY_TYPE_ULPI &&
	     hsotg->hw_params.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED &&
	     hsotg->params.ulpi_fs_ls) ||
	    hsotg->params.phy_type == DWC2_PHY_TYPE_PARAM_FS) {
		/* Full speed PHY */
		val = HCFG_FSLSPCLKSEL_48_MHZ;
	} else {
		/* High speed PHY running at full speed or high speed */
		val = HCFG_FSLSPCLKSEL_30_60_MHZ;
	}

	dev_dbg(hsotg->dev, "Initializing HCFG.FSLSPClkSel to %08x\n", val);
	hcfg = dwc2_readl(hsotg, HCFG);
	hcfg &= ~HCFG_FSLSPCLKSEL_MASK;
	hcfg |= val << HCFG_FSLSPCLKSEL_SHIFT;
	dwc2_writel(hsotg, hcfg, HCFG);
}