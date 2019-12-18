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
struct omap3isp_prev_csc {int** matrix; int* offset; } ;
struct prev_params {struct omap3isp_prev_csc csc; } ;
struct isp_prev_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPPRV_CSC0 ; 
 int ISPPRV_CSC0_BY_SHIFT ; 
 int ISPPRV_CSC0_GY_SHIFT ; 
 int ISPPRV_CSC0_RY_SHIFT ; 
 int /*<<< orphan*/  ISPPRV_CSC1 ; 
 int ISPPRV_CSC1_BCB_SHIFT ; 
 int ISPPRV_CSC1_GCB_SHIFT ; 
 int ISPPRV_CSC1_RCB_SHIFT ; 
 int /*<<< orphan*/  ISPPRV_CSC2 ; 
 int ISPPRV_CSC2_BCR_SHIFT ; 
 int ISPPRV_CSC2_GCR_SHIFT ; 
 int ISPPRV_CSC2_RCR_SHIFT ; 
 int /*<<< orphan*/  ISPPRV_CSC_OFFSET ; 
 int ISPPRV_CSC_OFFSET_CB_SHIFT ; 
 int ISPPRV_CSC_OFFSET_CR_SHIFT ; 
 int ISPPRV_CSC_OFFSET_Y_SHIFT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_PREV ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void
preview_config_csc(struct isp_prev_device *prev,
		   const struct prev_params *params)
{
	struct isp_device *isp = to_isp_device(prev);
	const struct omap3isp_prev_csc *csc = &params->csc;
	u32 val;

	val = (csc->matrix[0][0] & 0x3ff) << ISPPRV_CSC0_RY_SHIFT;
	val |= (csc->matrix[0][1] & 0x3ff) << ISPPRV_CSC0_GY_SHIFT;
	val |= (csc->matrix[0][2] & 0x3ff) << ISPPRV_CSC0_BY_SHIFT;
	isp_reg_writel(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_CSC0);

	val = (csc->matrix[1][0] & 0x3ff) << ISPPRV_CSC1_RCB_SHIFT;
	val |= (csc->matrix[1][1] & 0x3ff) << ISPPRV_CSC1_GCB_SHIFT;
	val |= (csc->matrix[1][2] & 0x3ff) << ISPPRV_CSC1_BCB_SHIFT;
	isp_reg_writel(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_CSC1);

	val = (csc->matrix[2][0] & 0x3ff) << ISPPRV_CSC2_RCR_SHIFT;
	val |= (csc->matrix[2][1] & 0x3ff) << ISPPRV_CSC2_GCR_SHIFT;
	val |= (csc->matrix[2][2] & 0x3ff) << ISPPRV_CSC2_BCR_SHIFT;
	isp_reg_writel(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_CSC2);

	val = (csc->offset[0] & 0xff) << ISPPRV_CSC_OFFSET_Y_SHIFT;
	val |= (csc->offset[1] & 0xff) << ISPPRV_CSC_OFFSET_CB_SHIFT;
	val |= (csc->offset[2] & 0xff) << ISPPRV_CSC_OFFSET_CR_SHIFT;
	isp_reg_writel(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_CSC_OFFSET);
}