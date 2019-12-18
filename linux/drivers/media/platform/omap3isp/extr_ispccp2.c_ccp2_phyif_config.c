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
struct isp_device {int /*<<< orphan*/  dev; } ;
struct isp_ccp2_device {int dummy; } ;
struct isp_ccp2_cfg {scalar_t__ phy_layer; scalar_t__ ccp2_mode; scalar_t__ strobe_clk_pol; scalar_t__ vp_clk_pol; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int EIO ; 
 int /*<<< orphan*/  ISPCCP2_CTRL ; 
 int /*<<< orphan*/  ISPCCP2_CTRL_INV_MASK ; 
 int /*<<< orphan*/  ISPCCP2_CTRL_INV_SHIFT ; 
 int /*<<< orphan*/  ISPCCP2_CTRL_IO_OUT_SEL_MASK ; 
 int /*<<< orphan*/  ISPCCP2_CTRL_IO_OUT_SEL_SHIFT ; 
 int ISPCCP2_CTRL_MODE ; 
 int /*<<< orphan*/  ISPCCP2_CTRL_PHY_SEL_MASK ; 
 int /*<<< orphan*/  ISPCCP2_CTRL_PHY_SEL_SHIFT ; 
 int /*<<< orphan*/  ISPCCP2_CTRL_VP_CLK_POL_MASK ; 
 int /*<<< orphan*/  ISPCCP2_CTRL_VP_CLK_POL_SHIFT ; 
 scalar_t__ ISP_CCP2_MODE_CCP2 ; 
 scalar_t__ ISP_CCP2_PHY_DATA_STROBE ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCP2 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccp2_device*) ; 

__attribute__((used)) static int ccp2_phyif_config(struct isp_ccp2_device *ccp2,
			     const struct isp_ccp2_cfg *buscfg)
{
	struct isp_device *isp = to_isp_device(ccp2);
	u32 val;

	val = isp_reg_readl(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL) |
			    ISPCCP2_CTRL_MODE;
	/* Data/strobe physical layer */
	BIT_SET(val, ISPCCP2_CTRL_PHY_SEL_SHIFT, ISPCCP2_CTRL_PHY_SEL_MASK,
		buscfg->phy_layer);
	BIT_SET(val, ISPCCP2_CTRL_IO_OUT_SEL_SHIFT,
		ISPCCP2_CTRL_IO_OUT_SEL_MASK, buscfg->ccp2_mode);
	BIT_SET(val, ISPCCP2_CTRL_INV_SHIFT, ISPCCP2_CTRL_INV_MASK,
		buscfg->strobe_clk_pol);
	BIT_SET(val, ISPCCP2_CTRL_VP_CLK_POL_SHIFT,
		ISPCCP2_CTRL_VP_CLK_POL_MASK, buscfg->vp_clk_pol);
	isp_reg_writel(isp, val, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL);

	val = isp_reg_readl(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL);
	if (!(val & ISPCCP2_CTRL_MODE)) {
		if (buscfg->ccp2_mode == ISP_CCP2_MODE_CCP2)
			dev_warn(isp->dev, "OMAP3 CCP2 bus not available\n");
		if (buscfg->phy_layer == ISP_CCP2_PHY_DATA_STROBE)
			/* Strobe mode requires CCP2 */
			return -EIO;
	}

	return 0;
}