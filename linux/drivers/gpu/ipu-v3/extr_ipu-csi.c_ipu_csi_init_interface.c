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
typedef  int /*<<< orphan*/  v4l2_std_id ;
typedef  int u32 ;
struct v4l2_mbus_framefmt {int width; int height; scalar_t__ field; } ;
struct v4l2_mbus_config {int dummy; } ;
struct ipu_csi_bus_config {int data_width; int data_fmt; int data_pol; int vsync_pol; int hsync_pol; int pixclk_pol; int ext_vsync; int clk_mode; int pack_tight; int force_eof; int data_en_pol; } ;
struct ipu_csi {int /*<<< orphan*/  lock; TYPE_1__* ipu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_ACT_FRM_SIZE ; 
 int /*<<< orphan*/  CSI_CCIR_CODE_1 ; 
 int /*<<< orphan*/  CSI_CCIR_CODE_3 ; 
 int CSI_CCIR_ERR_DET_EN ; 
 int /*<<< orphan*/  CSI_SENS_CONF ; 
 int CSI_SENS_CONF_DATA_EN_POL_SHIFT ; 
 int CSI_SENS_CONF_DATA_FMT_SHIFT ; 
 int CSI_SENS_CONF_DATA_POL_SHIFT ; 
 int CSI_SENS_CONF_DATA_WIDTH_SHIFT ; 
 int CSI_SENS_CONF_EXT_VSYNC_SHIFT ; 
 int CSI_SENS_CONF_FORCE_EOF_SHIFT ; 
 int CSI_SENS_CONF_HSYNC_POL_SHIFT ; 
 int CSI_SENS_CONF_PACK_TIGHT_SHIFT ; 
 int CSI_SENS_CONF_PIX_CLK_POL_SHIFT ; 
 int CSI_SENS_CONF_SENS_PRTCL_SHIFT ; 
 int CSI_SENS_CONF_VSYNC_POL_SHIFT ; 
 int /*<<< orphan*/  CSI_SENS_FRM_SIZE ; 
 int EINVAL ; 
#define  IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_DDR 135 
#define  IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_SDR 134 
#define  IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_DDR 133 
#define  IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_SDR 132 
#define  IPU_CSI_CLK_MODE_CCIR656_INTERLACED 131 
#define  IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE 130 
#define  IPU_CSI_CLK_MODE_GATED_CLK 129 
#define  IPU_CSI_CLK_MODE_NONGATED_CLK 128 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  V4L2_STD_PAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fill_csi_bus_cfg (struct ipu_csi_bus_config*,struct v4l2_mbus_config const*,struct v4l2_mbus_framefmt const*) ; 
 int /*<<< orphan*/  ipu_csi_read (struct ipu_csi*,int /*<<< orphan*/ ) ; 
 int ipu_csi_set_bt_interlaced_codes (struct ipu_csi*,struct v4l2_mbus_framefmt const*,struct v4l2_mbus_framefmt const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_write (struct ipu_csi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_csi_init_interface(struct ipu_csi *csi,
			   const struct v4l2_mbus_config *mbus_cfg,
			   const struct v4l2_mbus_framefmt *infmt,
			   const struct v4l2_mbus_framefmt *outfmt)
{
	struct ipu_csi_bus_config cfg;
	unsigned long flags;
	u32 width, height, data = 0;
	v4l2_std_id std;
	int ret;

	ret = fill_csi_bus_cfg(&cfg, mbus_cfg, infmt);
	if (ret < 0)
		return ret;

	/* set default sensor frame width and height */
	width = infmt->width;
	height = infmt->height;
	if (infmt->field == V4L2_FIELD_ALTERNATE)
		height *= 2;

	/* Set the CSI_SENS_CONF register remaining fields */
	data |= cfg.data_width << CSI_SENS_CONF_DATA_WIDTH_SHIFT |
		cfg.data_fmt << CSI_SENS_CONF_DATA_FMT_SHIFT |
		cfg.data_pol << CSI_SENS_CONF_DATA_POL_SHIFT |
		cfg.vsync_pol << CSI_SENS_CONF_VSYNC_POL_SHIFT |
		cfg.hsync_pol << CSI_SENS_CONF_HSYNC_POL_SHIFT |
		cfg.pixclk_pol << CSI_SENS_CONF_PIX_CLK_POL_SHIFT |
		cfg.ext_vsync << CSI_SENS_CONF_EXT_VSYNC_SHIFT |
		cfg.clk_mode << CSI_SENS_CONF_SENS_PRTCL_SHIFT |
		cfg.pack_tight << CSI_SENS_CONF_PACK_TIGHT_SHIFT |
		cfg.force_eof << CSI_SENS_CONF_FORCE_EOF_SHIFT |
		cfg.data_en_pol << CSI_SENS_CONF_DATA_EN_POL_SHIFT;

	spin_lock_irqsave(&csi->lock, flags);

	ipu_csi_write(csi, data, CSI_SENS_CONF);

	/* Set CCIR registers */

	switch (cfg.clk_mode) {
	case IPU_CSI_CLK_MODE_CCIR656_PROGRESSIVE:
		ipu_csi_write(csi, 0x40030, CSI_CCIR_CODE_1);
		ipu_csi_write(csi, 0xFF0000, CSI_CCIR_CODE_3);
		break;
	case IPU_CSI_CLK_MODE_CCIR656_INTERLACED:
		if (width == 720 && height == 480) {
			std = V4L2_STD_NTSC;
			height = 525;
		} else if (width == 720 && height == 576) {
			std = V4L2_STD_PAL;
			height = 625;
		} else {
			dev_err(csi->ipu->dev,
				"Unsupported interlaced video mode\n");
			ret = -EINVAL;
			goto out_unlock;
		}

		ret = ipu_csi_set_bt_interlaced_codes(csi, infmt, outfmt, std);
		if (ret)
			goto out_unlock;
		break;
	case IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_DDR:
	case IPU_CSI_CLK_MODE_CCIR1120_PROGRESSIVE_SDR:
	case IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_DDR:
	case IPU_CSI_CLK_MODE_CCIR1120_INTERLACED_SDR:
		ipu_csi_write(csi, 0x40030 | CSI_CCIR_ERR_DET_EN,
				   CSI_CCIR_CODE_1);
		ipu_csi_write(csi, 0xFF0000, CSI_CCIR_CODE_3);
		break;
	case IPU_CSI_CLK_MODE_GATED_CLK:
	case IPU_CSI_CLK_MODE_NONGATED_CLK:
		ipu_csi_write(csi, 0, CSI_CCIR_CODE_1);
		break;
	}

	/* Setup sensor frame size */
	ipu_csi_write(csi, (width - 1) | ((height - 1) << 16),
		      CSI_SENS_FRM_SIZE);

	dev_dbg(csi->ipu->dev, "CSI_SENS_CONF = 0x%08X\n",
		ipu_csi_read(csi, CSI_SENS_CONF));
	dev_dbg(csi->ipu->dev, "CSI_ACT_FRM_SIZE = 0x%08X\n",
		ipu_csi_read(csi, CSI_ACT_FRM_SIZE));

out_unlock:
	spin_unlock_irqrestore(&csi->lock, flags);

	return ret;
}