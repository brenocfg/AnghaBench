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
struct v4l2_subdev {int /*<<< orphan*/  name; int /*<<< orphan*/  entity; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct isp_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  src_ofst; int /*<<< orphan*/  vsize_count; int /*<<< orphan*/  hsize_count; } ;
struct isp_ccp2_device {int state; int /*<<< orphan*/  phy; int /*<<< orphan*/  input; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; TYPE_1__ mem_cfg; struct v4l2_mbus_framefmt* formats; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCP2_INPUT_MEMORY ; 
 int /*<<< orphan*/  CCP2_INPUT_SENSOR ; 
 size_t CCP2_PAD_SINK ; 
#define  ISP_PIPELINE_STREAM_CONTINUOUS 130 
#define  ISP_PIPELINE_STREAM_SINGLESHOT 129 
#define  ISP_PIPELINE_STREAM_STOPPED 128 
 int /*<<< orphan*/  OMAP3_ISP_SBL_CSI1_READ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp2_if_configure (struct isp_ccp2_device*) ; 
 int ccp2_if_enable (struct isp_ccp2_device*,int) ; 
 int /*<<< orphan*/  ccp2_mem_configure (struct isp_ccp2_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  ccp2_mem_enable (struct isp_ccp2_device*,int) ; 
 int /*<<< orphan*/  ccp2_print_status (struct isp_ccp2_device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int omap3isp_csiphy_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_csiphy_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_module_sync_idle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_sbl_disable (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_sbl_enable (struct isp_device*,int /*<<< orphan*/ ) ; 
 struct device* to_device (struct isp_ccp2_device*) ; 
 struct isp_device* to_isp_device (struct isp_ccp2_device*) ; 
 struct isp_ccp2_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ccp2_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct isp_ccp2_device *ccp2 = v4l2_get_subdevdata(sd);
	struct isp_device *isp = to_isp_device(ccp2);
	struct device *dev = to_device(ccp2);
	int ret;

	if (ccp2->state == ISP_PIPELINE_STREAM_STOPPED) {
		if (enable == ISP_PIPELINE_STREAM_STOPPED)
			return 0;
		atomic_set(&ccp2->stopping, 0);
	}

	switch (enable) {
	case ISP_PIPELINE_STREAM_CONTINUOUS:
		if (ccp2->phy) {
			ret = omap3isp_csiphy_acquire(ccp2->phy, &sd->entity);
			if (ret < 0)
				return ret;
		}

		ccp2_if_configure(ccp2);
		ccp2_print_status(ccp2);

		/* Enable CSI1/CCP2 interface */
		ret = ccp2_if_enable(ccp2, 1);
		if (ret < 0) {
			if (ccp2->phy)
				omap3isp_csiphy_release(ccp2->phy);
			return ret;
		}
		break;

	case ISP_PIPELINE_STREAM_SINGLESHOT:
		if (ccp2->state != ISP_PIPELINE_STREAM_SINGLESHOT) {
			struct v4l2_mbus_framefmt *format;

			format = &ccp2->formats[CCP2_PAD_SINK];

			ccp2->mem_cfg.hsize_count = format->width;
			ccp2->mem_cfg.vsize_count = format->height;
			ccp2->mem_cfg.src_ofst = 0;

			ccp2_mem_configure(ccp2, &ccp2->mem_cfg);
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_CSI1_READ);
			ccp2_print_status(ccp2);
		}
		ccp2_mem_enable(ccp2, 1);
		break;

	case ISP_PIPELINE_STREAM_STOPPED:
		if (omap3isp_module_sync_idle(&sd->entity, &ccp2->wait,
					      &ccp2->stopping))
			dev_dbg(dev, "%s: module stop timeout.\n", sd->name);
		if (ccp2->input == CCP2_INPUT_MEMORY) {
			ccp2_mem_enable(ccp2, 0);
			omap3isp_sbl_disable(isp, OMAP3_ISP_SBL_CSI1_READ);
		} else if (ccp2->input == CCP2_INPUT_SENSOR) {
			/* Disable CSI1/CCP2 interface */
			ccp2_if_enable(ccp2, 0);
			if (ccp2->phy)
				omap3isp_csiphy_release(ccp2->phy);
		}
		break;
	}

	ccp2->state = enable;
	return 0;
}