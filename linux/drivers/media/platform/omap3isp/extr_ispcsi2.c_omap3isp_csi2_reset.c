#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct isp_device {scalar_t__ revision; scalar_t__ autoidle; int /*<<< orphan*/  dev; } ;
struct isp_csi2_device {int /*<<< orphan*/  regs1; TYPE_1__* phy; int /*<<< orphan*/  available; struct isp_device* isp; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_regs; scalar_t__ entity; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  ISPCSI2_PHY_CFG ; 
 int /*<<< orphan*/  ISPCSI2_PHY_CFG_RESET_CTRL ; 
 int /*<<< orphan*/  ISPCSI2_SYSCONFIG ; 
 int ISPCSI2_SYSCONFIG_AUTO_IDLE ; 
 int ISPCSI2_SYSCONFIG_MSTANDBY_MODE_MASK ; 
 int ISPCSI2_SYSCONFIG_MSTANDBY_MODE_NO ; 
 int ISPCSI2_SYSCONFIG_MSTANDBY_MODE_SMART ; 
 int /*<<< orphan*/  ISPCSI2_SYSCONFIG_SOFT_RESET ; 
 int /*<<< orphan*/  ISPCSI2_SYSSTATUS ; 
 int ISPCSI2_SYSSTATUS_RESET_DONE ; 
 int /*<<< orphan*/  ISPCSIPHY_REG1 ; 
 int ISPCSIPHY_REG1_RESET_DONE_CTRLCLK ; 
 scalar_t__ ISP_REVISION_15_0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isp_reg_clr_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int omap3isp_csi2_reset(struct isp_csi2_device *csi2)
{
	struct isp_device *isp = csi2->isp;
	u8 soft_reset_retries = 0;
	u32 reg;
	int i;

	if (!csi2->available)
		return -ENODEV;

	if (csi2->phy->entity)
		return -EBUSY;

	isp_reg_set(isp, csi2->regs1, ISPCSI2_SYSCONFIG,
		    ISPCSI2_SYSCONFIG_SOFT_RESET);

	do {
		reg = isp_reg_readl(isp, csi2->regs1, ISPCSI2_SYSSTATUS) &
				    ISPCSI2_SYSSTATUS_RESET_DONE;
		if (reg == ISPCSI2_SYSSTATUS_RESET_DONE)
			break;
		soft_reset_retries++;
		if (soft_reset_retries < 5)
			udelay(100);
	} while (soft_reset_retries < 5);

	if (soft_reset_retries == 5) {
		dev_err(isp->dev, "CSI2: Soft reset try count exceeded!\n");
		return -EBUSY;
	}

	if (isp->revision == ISP_REVISION_15_0)
		isp_reg_set(isp, csi2->regs1, ISPCSI2_PHY_CFG,
			    ISPCSI2_PHY_CFG_RESET_CTRL);

	i = 100;
	do {
		reg = isp_reg_readl(isp, csi2->phy->phy_regs, ISPCSIPHY_REG1)
		    & ISPCSIPHY_REG1_RESET_DONE_CTRLCLK;
		if (reg == ISPCSIPHY_REG1_RESET_DONE_CTRLCLK)
			break;
		udelay(100);
	} while (--i > 0);

	if (i == 0) {
		dev_err(isp->dev,
			"CSI2: Reset for CSI2_96M_FCLK domain Failed!\n");
		return -EBUSY;
	}

	if (isp->autoidle)
		isp_reg_clr_set(isp, csi2->regs1, ISPCSI2_SYSCONFIG,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_MASK |
				ISPCSI2_SYSCONFIG_AUTO_IDLE,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_SMART |
				((isp->revision == ISP_REVISION_15_0) ?
				 ISPCSI2_SYSCONFIG_AUTO_IDLE : 0));
	else
		isp_reg_clr_set(isp, csi2->regs1, ISPCSI2_SYSCONFIG,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_MASK |
				ISPCSI2_SYSCONFIG_AUTO_IDLE,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_NO);

	return 0;
}