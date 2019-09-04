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
struct isp_csiphy {int /*<<< orphan*/  phy_regs; int /*<<< orphan*/  cfg_regs; int /*<<< orphan*/  num_data_lanes; int /*<<< orphan*/ * csi2; int /*<<< orphan*/  mutex; struct isp_device* isp; } ;
struct isp_device {scalar_t__ revision; int /*<<< orphan*/  isp_csi2c; int /*<<< orphan*/  isp_csi2a; struct isp_csiphy isp_csiphy2; struct isp_csiphy isp_csiphy1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_CSIPHY1_NUM_DATA_LANES ; 
 int /*<<< orphan*/  ISP_CSIPHY2_NUM_DATA_LANES ; 
 scalar_t__ ISP_REVISION_15_0 ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CSI2A_REGS1 ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CSI2C_REGS1 ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CSIPHY1 ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CSIPHY2 ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int omap3isp_csiphy_init(struct isp_device *isp)
{
	struct isp_csiphy *phy1 = &isp->isp_csiphy1;
	struct isp_csiphy *phy2 = &isp->isp_csiphy2;

	phy2->isp = isp;
	phy2->csi2 = &isp->isp_csi2a;
	phy2->num_data_lanes = ISP_CSIPHY2_NUM_DATA_LANES;
	phy2->cfg_regs = OMAP3_ISP_IOMEM_CSI2A_REGS1;
	phy2->phy_regs = OMAP3_ISP_IOMEM_CSIPHY2;
	mutex_init(&phy2->mutex);

	phy1->isp = isp;
	mutex_init(&phy1->mutex);

	if (isp->revision == ISP_REVISION_15_0) {
		phy1->csi2 = &isp->isp_csi2c;
		phy1->num_data_lanes = ISP_CSIPHY1_NUM_DATA_LANES;
		phy1->cfg_regs = OMAP3_ISP_IOMEM_CSI2C_REGS1;
		phy1->phy_regs = OMAP3_ISP_IOMEM_CSIPHY1;
	}

	return 0;
}