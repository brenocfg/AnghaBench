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
struct v4l2_subdev {int dummy; } ;
struct isp_device {int dummy; } ;
struct isp_ccdc_device {int state; int output; int /*<<< orphan*/  underrun; } ;

/* Variables and functions */
 int CCDC_OUTPUT_MEMORY ; 
 int /*<<< orphan*/  ISPCCDC_CFG ; 
 int /*<<< orphan*/  ISPCCDC_CFG_VDLC ; 
#define  ISP_PIPELINE_STREAM_CONTINUOUS 130 
#define  ISP_PIPELINE_STREAM_SINGLESHOT 129 
#define  ISP_PIPELINE_STREAM_STOPPED 128 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 int /*<<< orphan*/  OMAP3_ISP_SBL_CCDC_WRITE ; 
 int /*<<< orphan*/  OMAP3_ISP_SUBCLK_CCDC ; 
 int /*<<< orphan*/  ccdc_configure (struct isp_ccdc_device*) ; 
 int ccdc_disable (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_enable (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_print_status (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_sbl_disable (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_sbl_enable (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_subclk_disable (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_subclk_enable (struct isp_device*,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 
 struct isp_ccdc_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ccdc_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	struct isp_device *isp = to_isp_device(ccdc);
	int ret = 0;

	if (ccdc->state == ISP_PIPELINE_STREAM_STOPPED) {
		if (enable == ISP_PIPELINE_STREAM_STOPPED)
			return 0;

		omap3isp_subclk_enable(isp, OMAP3_ISP_SUBCLK_CCDC);
		isp_reg_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG,
			    ISPCCDC_CFG_VDLC);

		ccdc_configure(ccdc);

		ccdc_print_status(ccdc);
	}

	switch (enable) {
	case ISP_PIPELINE_STREAM_CONTINUOUS:
		if (ccdc->output & CCDC_OUTPUT_MEMORY)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_CCDC_WRITE);

		if (ccdc->underrun || !(ccdc->output & CCDC_OUTPUT_MEMORY))
			ccdc_enable(ccdc);

		ccdc->underrun = 0;
		break;

	case ISP_PIPELINE_STREAM_SINGLESHOT:
		if (ccdc->output & CCDC_OUTPUT_MEMORY &&
		    ccdc->state != ISP_PIPELINE_STREAM_SINGLESHOT)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_CCDC_WRITE);

		ccdc_enable(ccdc);
		break;

	case ISP_PIPELINE_STREAM_STOPPED:
		ret = ccdc_disable(ccdc);
		if (ccdc->output & CCDC_OUTPUT_MEMORY)
			omap3isp_sbl_disable(isp, OMAP3_ISP_SBL_CCDC_WRITE);
		omap3isp_subclk_disable(isp, OMAP3_ISP_SUBCLK_CCDC);
		ccdc->underrun = 0;
		break;
	}

	ccdc->state = enable;
	return ret;
}