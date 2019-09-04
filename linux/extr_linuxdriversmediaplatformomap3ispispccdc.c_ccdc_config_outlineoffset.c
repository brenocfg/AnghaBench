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
struct isp_ccdc_device {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCCDC_HSIZE_OFF ; 
 int /*<<< orphan*/  ISPCCDC_SDOFST ; 
 int ISPCCDC_SDOFST_LOFST0_SHIFT ; 
 int ISPCCDC_SDOFST_LOFST1_SHIFT ; 
 int ISPCCDC_SDOFST_LOFST2_SHIFT ; 
 int ISPCCDC_SDOFST_LOFST3_SHIFT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
#define  V4L2_FIELD_INTERLACED_BT 129 
#define  V4L2_FIELD_INTERLACED_TB 128 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 

__attribute__((used)) static void ccdc_config_outlineoffset(struct isp_ccdc_device *ccdc,
				      unsigned int bpl,
				      enum v4l2_field field)
{
	struct isp_device *isp = to_isp_device(ccdc);
	u32 sdofst = 0;

	isp_reg_writel(isp, bpl & 0xffff, OMAP3_ISP_IOMEM_CCDC,
		       ISPCCDC_HSIZE_OFF);

	switch (field) {
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_INTERLACED_BT:
		/* When interleaving fields in memory offset field one by one
		 * line and set the line offset to two lines.
		 */
		sdofst |= (1 << ISPCCDC_SDOFST_LOFST0_SHIFT)
		       |  (1 << ISPCCDC_SDOFST_LOFST1_SHIFT)
		       |  (1 << ISPCCDC_SDOFST_LOFST2_SHIFT)
		       |  (1 << ISPCCDC_SDOFST_LOFST3_SHIFT);
		break;

	default:
		/* In all other cases set the line offsets to one line. */
		break;
	}

	isp_reg_writel(isp, sdofst, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SDOFST);
}