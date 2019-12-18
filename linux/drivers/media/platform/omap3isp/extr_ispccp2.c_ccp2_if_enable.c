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
typedef  scalar_t__ u8 ;
struct isp_device {int dummy; } ;
struct isp_ccp2_device {scalar_t__ vdds_csib; } ;

/* Variables and functions */
 int CCP2_LCx_CHANS_NUM ; 
 int /*<<< orphan*/  ISPCCP2_CTRL ; 
 int ISPCCP2_CTRL_IF_EN ; 
 int ISPCCP2_CTRL_MODE ; 
 int /*<<< orphan*/  ISPCCP2_LCx_CTRL (int) ; 
 int ISPCCP2_LCx_CTRL_CHAN_EN ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCP2 ; 
 int /*<<< orphan*/  isp_reg_clr_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 struct isp_device* to_isp_device (struct isp_ccp2_device*) ; 

__attribute__((used)) static int ccp2_if_enable(struct isp_ccp2_device *ccp2, u8 enable)
{
	struct isp_device *isp = to_isp_device(ccp2);
	int ret;
	int i;

	if (enable && ccp2->vdds_csib) {
		ret = regulator_enable(ccp2->vdds_csib);
		if (ret < 0)
			return ret;
	}

	/* Enable/Disable all the LCx channels */
	for (i = 0; i < CCP2_LCx_CHANS_NUM; i++)
		isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_CTRL(i),
				ISPCCP2_LCx_CTRL_CHAN_EN,
				enable ? ISPCCP2_LCx_CTRL_CHAN_EN : 0);

	/* Enable/Disable ccp2 interface in ccp2 mode */
	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL,
			ISPCCP2_CTRL_MODE | ISPCCP2_CTRL_IF_EN,
			enable ? (ISPCCP2_CTRL_MODE | ISPCCP2_CTRL_IF_EN) : 0);

	if (!enable && ccp2->vdds_csib)
		regulator_disable(ccp2->vdds_csib);

	return 0;
}