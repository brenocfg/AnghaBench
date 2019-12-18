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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  code; } ;
struct v4l2_mbus_config {int type; int flags; } ;
struct ipu_csi_bus_config {int ext_vsync; int vsync_pol; int hsync_pol; int pixclk_pol; int /*<<< orphan*/  clk_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CSI_CLK_MODE_CCIR656_INTERLACED ; 
 int /*<<< orphan*/  IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE ; 
 int /*<<< orphan*/  IPU_CSI_CLK_MODE_GATED_CLK ; 
 int /*<<< orphan*/  IPU_CSI_CLK_MODE_NONGATED_CLK ; 
 int /*<<< orphan*/  V4L2_FIELD_ALTERNATE ; 
 int /*<<< orphan*/  V4L2_FIELD_HAS_BOTH (int /*<<< orphan*/ ) ; 
#define  V4L2_MBUS_BT656 130 
#define  V4L2_MBUS_CSI2_DPHY 129 
 int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
#define  V4L2_MBUS_PARALLEL 128 
 int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int mbus_code_to_bus_cfg (struct ipu_csi_bus_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ipu_csi_bus_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fill_csi_bus_cfg(struct ipu_csi_bus_config *csicfg,
			    const struct v4l2_mbus_config *mbus_cfg,
			    const struct v4l2_mbus_framefmt *mbus_fmt)
{
	int ret;

	memset(csicfg, 0, sizeof(*csicfg));

	ret = mbus_code_to_bus_cfg(csicfg, mbus_fmt->code, mbus_cfg->type);
	if (ret < 0)
		return ret;

	switch (mbus_cfg->type) {
	case V4L2_MBUS_PARALLEL:
		csicfg->ext_vsync = 1;
		csicfg->vsync_pol = (mbus_cfg->flags &
				     V4L2_MBUS_VSYNC_ACTIVE_LOW) ? 1 : 0;
		csicfg->hsync_pol = (mbus_cfg->flags &
				     V4L2_MBUS_HSYNC_ACTIVE_LOW) ? 1 : 0;
		csicfg->pixclk_pol = (mbus_cfg->flags &
				      V4L2_MBUS_PCLK_SAMPLE_FALLING) ? 1 : 0;
		csicfg->clk_mode = IPU_CSI_CLK_MODE_GATED_CLK;
		break;
	case V4L2_MBUS_BT656:
		csicfg->ext_vsync = 0;
		if (V4L2_FIELD_HAS_BOTH(mbus_fmt->field) ||
		    mbus_fmt->field == V4L2_FIELD_ALTERNATE)
			csicfg->clk_mode = IPU_CSI_CLK_MODE_CCIR656_INTERLACED;
		else
			csicfg->clk_mode = IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE;
		break;
	case V4L2_MBUS_CSI2_DPHY:
		/*
		 * MIPI CSI-2 requires non gated clock mode, all other
		 * parameters are not applicable for MIPI CSI-2 bus.
		 */
		csicfg->clk_mode = IPU_CSI_CLK_MODE_NONGATED_CLK;
		break;
	default:
		/* will never get here, keep compiler quiet */
		break;
	}

	return 0;
}