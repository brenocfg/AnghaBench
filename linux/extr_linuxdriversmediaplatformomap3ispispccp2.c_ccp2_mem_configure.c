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
typedef  scalar_t__ u32 ;
struct isp_interface_mem_config {int hsize_count; scalar_t__ vsize_count; scalar_t__ src_ofst; } ;
struct isp_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ bpl_padding; scalar_t__ bpl_value; } ;
struct isp_ccp2_device {TYPE_2__ video_in; TYPE_1__* formats; } ;
struct TYPE_3__ {scalar_t__ code; } ;

/* Variables and functions */
 size_t CCP2_PAD_SINK ; 
 size_t CCP2_PAD_SOURCE ; 
 int /*<<< orphan*/  ISPCCP2_CTRL ; 
 scalar_t__ ISPCCP2_CTRL_IO_OUT_SEL ; 
 scalar_t__ ISPCCP2_CTRL_MODE ; 
 int /*<<< orphan*/  ISPCCP2_LCM_CTRL ; 
 scalar_t__ ISPCCP2_LCM_CTRL_BURST_SIZE_32X ; 
 scalar_t__ ISPCCP2_LCM_CTRL_BURST_SIZE_SHIFT ; 
 scalar_t__ ISPCCP2_LCM_CTRL_DST_FORMAT_RAW10 ; 
 scalar_t__ ISPCCP2_LCM_CTRL_DST_FORMAT_SHIFT ; 
 scalar_t__ ISPCCP2_LCM_CTRL_SRC_DECOMPR_DPCM10 ; 
 scalar_t__ ISPCCP2_LCM_CTRL_SRC_DECOMPR_SHIFT ; 
 scalar_t__ ISPCCP2_LCM_CTRL_SRC_DPCM_PRED ; 
 scalar_t__ ISPCCP2_LCM_CTRL_SRC_FORMAT_RAW10 ; 
 scalar_t__ ISPCCP2_LCM_CTRL_SRC_FORMAT_RAW8 ; 
 scalar_t__ ISPCCP2_LCM_CTRL_SRC_FORMAT_SHIFT ; 
 int /*<<< orphan*/  ISPCCP2_LCM_HSIZE ; 
 int ISPCCP2_LCM_HSIZE_SHIFT ; 
 int ISPCCP2_LCM_HSIZE_SKIP_MIN ; 
 int /*<<< orphan*/  ISPCCP2_LCM_IRQENABLE ; 
 int /*<<< orphan*/  ISPCCP2_LCM_IRQSTATUS ; 
 scalar_t__ ISPCCP2_LCM_IRQSTATUS_EOF_IRQ ; 
 scalar_t__ ISPCCP2_LCM_IRQSTATUS_OCPERROR_IRQ ; 
 int /*<<< orphan*/  ISPCCP2_LCM_PREFETCH ; 
 scalar_t__ ISPCCP2_LCM_PREFETCH_SHIFT ; 
 int /*<<< orphan*/  ISPCCP2_LCM_SRC_OFST ; 
 int /*<<< orphan*/  ISPCCP2_LCM_VSIZE ; 
 scalar_t__ ISPCCP2_LCM_VSIZE_SHIFT ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCP2 ; 
 int /*<<< orphan*/  ccp2_adjust_bandwidth (struct isp_ccp2_device*) ; 
 int /*<<< orphan*/  ccp2_pwr_cfg (struct isp_ccp2_device*) ; 
 int /*<<< orphan*/  ccp2_vp_config (struct isp_ccp2_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccp2_device*) ; 

__attribute__((used)) static void ccp2_mem_configure(struct isp_ccp2_device *ccp2,
			       struct isp_interface_mem_config *config)
{
	struct isp_device *isp = to_isp_device(ccp2);
	u32 sink_pixcode = ccp2->formats[CCP2_PAD_SINK].code;
	u32 source_pixcode = ccp2->formats[CCP2_PAD_SOURCE].code;
	unsigned int dpcm_decompress = 0;
	u32 val, hwords;

	if (sink_pixcode != source_pixcode &&
	    sink_pixcode == MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8)
		dpcm_decompress = 1;

	ccp2_pwr_cfg(ccp2);

	/* Hsize, Skip */
	isp_reg_writel(isp, ISPCCP2_LCM_HSIZE_SKIP_MIN |
		       (config->hsize_count << ISPCCP2_LCM_HSIZE_SHIFT),
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_HSIZE);

	/* Vsize, no. of lines */
	isp_reg_writel(isp, config->vsize_count << ISPCCP2_LCM_VSIZE_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_VSIZE);

	if (ccp2->video_in.bpl_padding == 0)
		config->src_ofst = 0;
	else
		config->src_ofst = ccp2->video_in.bpl_value;

	isp_reg_writel(isp, config->src_ofst, OMAP3_ISP_IOMEM_CCP2,
		       ISPCCP2_LCM_SRC_OFST);

	/* Source and Destination formats */
	val = ISPCCP2_LCM_CTRL_DST_FORMAT_RAW10 <<
	      ISPCCP2_LCM_CTRL_DST_FORMAT_SHIFT;

	if (dpcm_decompress) {
		/* source format is RAW8 */
		val |= ISPCCP2_LCM_CTRL_SRC_FORMAT_RAW8 <<
		       ISPCCP2_LCM_CTRL_SRC_FORMAT_SHIFT;

		/* RAW8 + DPCM10 - simple predictor */
		val |= ISPCCP2_LCM_CTRL_SRC_DPCM_PRED;

		/* enable source DPCM decompression */
		val |= ISPCCP2_LCM_CTRL_SRC_DECOMPR_DPCM10 <<
		       ISPCCP2_LCM_CTRL_SRC_DECOMPR_SHIFT;
	} else {
		/* source format is RAW10 */
		val |= ISPCCP2_LCM_CTRL_SRC_FORMAT_RAW10 <<
		       ISPCCP2_LCM_CTRL_SRC_FORMAT_SHIFT;
	}

	/* Burst size to 32x64 */
	val |= ISPCCP2_LCM_CTRL_BURST_SIZE_32X <<
	       ISPCCP2_LCM_CTRL_BURST_SIZE_SHIFT;

	isp_reg_writel(isp, val, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_CTRL);

	/* Prefetch setup */
	if (dpcm_decompress)
		hwords = (ISPCCP2_LCM_HSIZE_SKIP_MIN +
			  config->hsize_count) >> 3;
	else
		hwords = (ISPCCP2_LCM_HSIZE_SKIP_MIN +
			  config->hsize_count) >> 2;

	isp_reg_writel(isp, hwords << ISPCCP2_LCM_PREFETCH_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_PREFETCH);

	/* Video port */
	isp_reg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTRL,
		    ISPCCP2_CTRL_IO_OUT_SEL | ISPCCP2_CTRL_MODE);
	ccp2_vp_config(ccp2, ccp2_adjust_bandwidth(ccp2));

	/* Clear LCM interrupts */
	isp_reg_writel(isp, ISPCCP2_LCM_IRQSTATUS_OCPERROR_IRQ |
		       ISPCCP2_LCM_IRQSTATUS_EOF_IRQ,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_IRQSTATUS);

	/* Enable LCM interrupts */
	isp_reg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_LCM_IRQENABLE,
		    ISPCCP2_LCM_IRQSTATUS_EOF_IRQ |
		    ISPCCP2_LCM_IRQSTATUS_OCPERROR_IRQ);
}