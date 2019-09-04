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
struct v4l2_mbus_framefmt {scalar_t__ code; } ;
struct isp_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct isp_ccdc_device {TYPE_1__ lsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_PAD_SINK ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ISPCCDC_LSC_CONFIG ; 
 int /*<<< orphan*/  ISPCCDC_LSC_ENABLE ; 
 int /*<<< orphan*/  LSC_STATE_RUNNING ; 
 int /*<<< orphan*/  LSC_STATE_STOPPED ; 
 int /*<<< orphan*/  LSC_STATE_STOPPING ; 
 scalar_t__ MEDIA_BUS_FMT_SBGGR10_1X10 ; 
 scalar_t__ MEDIA_BUS_FMT_SGBRG10_1X10 ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 scalar_t__ MEDIA_BUS_FMT_SRGGB10_1X10 ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 int /*<<< orphan*/  OMAP3_ISP_SBL_CCDC_LSC_READ ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct v4l2_mbus_framefmt* __ccdc_get_format (struct isp_ccdc_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ccdc_lsc_wait_prefetch (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isp_reg_clr (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_clr_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_sbl_enable (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_device (struct isp_ccdc_device*) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 

__attribute__((used)) static int __ccdc_lsc_enable(struct isp_ccdc_device *ccdc, int enable)
{
	struct isp_device *isp = to_isp_device(ccdc);
	const struct v4l2_mbus_framefmt *format =
		__ccdc_get_format(ccdc, NULL, CCDC_PAD_SINK,
				  V4L2_SUBDEV_FORMAT_ACTIVE);

	if ((format->code != MEDIA_BUS_FMT_SGRBG10_1X10) &&
	    (format->code != MEDIA_BUS_FMT_SRGGB10_1X10) &&
	    (format->code != MEDIA_BUS_FMT_SBGGR10_1X10) &&
	    (format->code != MEDIA_BUS_FMT_SGBRG10_1X10))
		return -EINVAL;

	if (enable)
		omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_CCDC_LSC_READ);

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_LSC_CONFIG,
			ISPCCDC_LSC_ENABLE, enable ? ISPCCDC_LSC_ENABLE : 0);

	if (enable) {
		if (ccdc_lsc_wait_prefetch(ccdc) < 0) {
			isp_reg_clr(isp, OMAP3_ISP_IOMEM_CCDC,
				    ISPCCDC_LSC_CONFIG, ISPCCDC_LSC_ENABLE);
			ccdc->lsc.state = LSC_STATE_STOPPED;
			dev_warn(to_device(ccdc), "LSC prefetch timeout\n");
			return -ETIMEDOUT;
		}
		ccdc->lsc.state = LSC_STATE_RUNNING;
	} else {
		ccdc->lsc.state = LSC_STATE_STOPPING;
	}

	return 0;
}