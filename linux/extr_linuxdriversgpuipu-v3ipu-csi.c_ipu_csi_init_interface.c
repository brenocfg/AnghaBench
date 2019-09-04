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
typedef  int u32 ;
struct v4l2_mbus_framefmt {int width; int height; } ;
struct v4l2_mbus_config {int dummy; } ;
struct ipu_csi_bus_config {int data_width; int data_fmt; int data_pol; int vsync_pol; int hsync_pol; int pixclk_pol; int ext_vsync; int clk_mode; int pack_tight; int force_eof; int data_en_pol; } ;
struct ipu_csi {int /*<<< orphan*/  lock; TYPE_1__* ipu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_ACT_FRM_SIZE ; 
 int /*<<< orphan*/  CSI_CCIR_CODE_1 ; 
 int /*<<< orphan*/  CSI_CCIR_CODE_2 ; 
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
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fill_csi_bus_cfg (struct ipu_csi_bus_config*,struct v4l2_mbus_config*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  ipu_csi_read (struct ipu_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_write (struct ipu_csi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_csi_init_interface(struct ipu_csi *csi,
			   struct v4l2_mbus_config *mbus_cfg,
			   struct v4l2_mbus_framefmt *mbus_fmt)
{
	struct ipu_csi_bus_config cfg;
	unsigned long flags;
	u32 width, height, data = 0;
	int ret;

	ret = fill_csi_bus_cfg(&cfg, mbus_cfg, mbus_fmt);
	if (ret < 0)
		return ret;

	/* set default sensor frame width and height */
	width = mbus_fmt->width;
	height = mbus_fmt->height;

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
		if (mbus_fmt->width == 720 && mbus_fmt->height == 576) {
			/*
			 * PAL case
			 *
			 * Field0BlankEnd = 0x6, Field0BlankStart = 0x2,
			 * Field0ActiveEnd = 0x4, Field0ActiveStart = 0
			 * Field1BlankEnd = 0x7, Field1BlankStart = 0x3,
			 * Field1ActiveEnd = 0x5, Field1ActiveStart = 0x1
			 */
			height = 625; /* framelines for PAL */

			ipu_csi_write(csi, 0x40596 | CSI_CCIR_ERR_DET_EN,
					  CSI_CCIR_CODE_1);
			ipu_csi_write(csi, 0xD07DF, CSI_CCIR_CODE_2);
			ipu_csi_write(csi, 0xFF0000, CSI_CCIR_CODE_3);
		} else if (mbus_fmt->width == 720 && mbus_fmt->height == 480) {
			/*
			 * NTSC case
			 *
			 * Field0BlankEnd = 0x7, Field0BlankStart = 0x3,
			 * Field0ActiveEnd = 0x5, Field0ActiveStart = 0x1
			 * Field1BlankEnd = 0x6, Field1BlankStart = 0x2,
			 * Field1ActiveEnd = 0x4, Field1ActiveStart = 0
			 */
			height = 525; /* framelines for NTSC */

			ipu_csi_write(csi, 0xD07DF | CSI_CCIR_ERR_DET_EN,
					  CSI_CCIR_CODE_1);
			ipu_csi_write(csi, 0x40596, CSI_CCIR_CODE_2);
			ipu_csi_write(csi, 0xFF0000, CSI_CCIR_CODE_3);
		} else {
			dev_err(csi->ipu->dev,
				"Unsupported CCIR656 interlaced video mode\n");
			spin_unlock_irqrestore(&csi->lock, flags);
			return -EINVAL;
		}
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

	spin_unlock_irqrestore(&csi->lock, flags);

	return 0;
}