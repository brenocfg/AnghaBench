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
struct isp_interface_lcx_config {int format; int crc; int data_start; int data_size; } ;
struct isp_device {scalar_t__ revision; } ;
struct isp_ccp2_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISPCCP2_LC01_IRQENABLE ; 
 int /*<<< orphan*/  ISPCCP2_LC01_IRQSTATUS ; 
 int ISPCCP2_LC01_IRQSTATUS_LC0_CRC_IRQ ; 
 int ISPCCP2_LC01_IRQSTATUS_LC0_FIFO_OVF_IRQ ; 
 int ISPCCP2_LC01_IRQSTATUS_LC0_FSC_IRQ ; 
 int ISPCCP2_LC01_IRQSTATUS_LC0_FSP_IRQ ; 
 int ISPCCP2_LC01_IRQSTATUS_LC0_FW_IRQ ; 
 int ISPCCP2_LC01_IRQSTATUS_LC0_SSC_IRQ ; 
 int /*<<< orphan*/  ISPCCP2_LCx_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISPCCP2_LCx_CTRL_CRC_MASK ; 
 int /*<<< orphan*/  ISPCCP2_LCx_CTRL_CRC_SHIFT ; 
 int /*<<< orphan*/  ISPCCP2_LCx_CTRL_CRC_SHIFT_15_0 ; 
 int /*<<< orphan*/  ISPCCP2_LCx_CTRL_FORMAT_MASK ; 
 int /*<<< orphan*/  ISPCCP2_LCx_CTRL_FORMAT_MASK_15_0 ; 
 int ISPCCP2_LCx_CTRL_FORMAT_RAW10_VP ; 
 int ISPCCP2_LCx_CTRL_FORMAT_RAW8_DPCM10_VP ; 
 int /*<<< orphan*/  ISPCCP2_LCx_CTRL_FORMAT_SHIFT ; 
 int /*<<< orphan*/  ISPCCP2_LCx_CTRL_FORMAT_SHIFT_15_0 ; 
 int ISPCCP2_LCx_CTRL_REGION_EN ; 
 int ISPCCP2_LCx_DAT_SHIFT ; 
 int /*<<< orphan*/  ISPCCP2_LCx_DAT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISPCCP2_LCx_DAT_START (int /*<<< orphan*/ ) ; 
 scalar_t__ ISP_REVISION_15_0 ; 
#define  MEDIA_BUS_FMT_SGRBG10_1X10 129 
#define  MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 128 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCP2 ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccp2_device*) ; 

__attribute__((used)) static void ccp2_lcx_config(struct isp_ccp2_device *ccp2,
			    struct isp_interface_lcx_config *config)
{
	struct isp_device *isp = to_isp_device(ccp2);
	u32 val, format;

	switch (config->format) {
	case MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
		format = ISPCCP2_LCx_CTRL_FORMAT_RAW8_DPCM10_VP;
		break;
	case MEDIA_BUS_FMT_SGRBG10_1X10:
	default:
		format = ISPCCP2_LCx_CTRL_FORMAT_RAW10_VP;	/* RAW10+VP */
		break;
	}
	/* ISPCCP2_LCx_CTRL logical channel #0 */
	val = isp_reg_readl(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_CTRL(0))
			    | (ISPCCP2_LCx_CTRL_REGION_EN); /* Region */

	if (isp->revision == ISP_REVISION_15_0) {
		/* CRC */
		BIT_SET(val, ISPCCP2_LCx_CTRL_CRC_SHIFT_15_0,
			ISPCCP2_LCx_CTRL_CRC_MASK,
			config->crc);
		/* Format = RAW10+VP or RAW8+DPCM10+VP*/
		BIT_SET(val, ISPCCP2_LCx_CTRL_FORMAT_SHIFT_15_0,
			ISPCCP2_LCx_CTRL_FORMAT_MASK_15_0, format);
	} else {
		BIT_SET(val, ISPCCP2_LCx_CTRL_CRC_SHIFT,
			ISPCCP2_LCx_CTRL_CRC_MASK,
			config->crc);

		BIT_SET(val, ISPCCP2_LCx_CTRL_FORMAT_SHIFT,
			ISPCCP2_LCx_CTRL_FORMAT_MASK, format);
	}
	isp_reg_writel(isp, val, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_CTRL(0));

	/* ISPCCP2_DAT_START for logical channel #0 */
	isp_reg_writel(isp, config->data_start << ISPCCP2_LCx_DAT_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_DAT_START(0));

	/* ISPCCP2_DAT_SIZE for logical channel #0 */
	isp_reg_writel(isp, config->data_size << ISPCCP2_LCx_DAT_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCx_DAT_SIZE(0));

	/* Enable error IRQs for logical channel #0 */
	val = ISPCCP2_LC01_IRQSTATUS_LC0_FIFO_OVF_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_CRC_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_FSP_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_FW_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_FSC_IRQ |
	      ISPCCP2_LC01_IRQSTATUS_LC0_SSC_IRQ;

	isp_reg_writel(isp, val, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LC01_IRQSTATUS);
	isp_reg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LC01_IRQENABLE, val);
}