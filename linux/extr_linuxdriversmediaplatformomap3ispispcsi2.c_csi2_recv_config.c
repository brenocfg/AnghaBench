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
struct isp_device {int dummy; } ;
struct isp_csi2_device {int /*<<< orphan*/  regs1; } ;
struct isp_csi2_ctrl_cfg {int vp_out_ctrl; scalar_t__ ecc_enable; scalar_t__ vp_only_enable; scalar_t__ vp_clk_enable; scalar_t__ frame_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCSI2_CTRL ; 
 int ISPCSI2_CTRL_ECC_EN ; 
 int ISPCSI2_CTRL_FRAME ; 
 int ISPCSI2_CTRL_VP_CLK_EN ; 
 int ISPCSI2_CTRL_VP_ONLY_EN ; 
 int ISPCSI2_CTRL_VP_OUT_CTRL_MASK ; 
 int ISPCSI2_CTRL_VP_OUT_CTRL_SHIFT ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi2_recv_config(struct isp_device *isp,
			     struct isp_csi2_device *csi2,
			     struct isp_csi2_ctrl_cfg *currctrl)
{
	u32 reg;

	reg = isp_reg_readl(isp, csi2->regs1, ISPCSI2_CTRL);

	if (currctrl->frame_mode)
		reg |= ISPCSI2_CTRL_FRAME;
	else
		reg &= ~ISPCSI2_CTRL_FRAME;

	if (currctrl->vp_clk_enable)
		reg |= ISPCSI2_CTRL_VP_CLK_EN;
	else
		reg &= ~ISPCSI2_CTRL_VP_CLK_EN;

	if (currctrl->vp_only_enable)
		reg |= ISPCSI2_CTRL_VP_ONLY_EN;
	else
		reg &= ~ISPCSI2_CTRL_VP_ONLY_EN;

	reg &= ~ISPCSI2_CTRL_VP_OUT_CTRL_MASK;
	reg |= currctrl->vp_out_ctrl << ISPCSI2_CTRL_VP_OUT_CTRL_SHIFT;

	if (currctrl->ecc_enable)
		reg |= ISPCSI2_CTRL_ECC_EN;
	else
		reg &= ~ISPCSI2_CTRL_ECC_EN;

	isp_reg_writel(isp, reg, csi2->regs1, ISPCSI2_CTRL);
}