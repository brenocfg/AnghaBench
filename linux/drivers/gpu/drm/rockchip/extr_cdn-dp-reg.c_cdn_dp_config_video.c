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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct video_info {int color_fmt; int color_depth; int h_sync_polarity; int v_sync_polarity; } ;
struct drm_display_mode {int clock; int hsync_start; int hdisplay; int htotal; int hsync_end; int vtotal; int vsync_start; int vsync_end; int vdisplay; } ;
struct TYPE_2__ {int rate; int num_lanes; } ;
struct cdn_dp_device {int /*<<< orphan*/  dev; TYPE_1__ link; struct drm_display_mode mode; struct video_info video_info; } ;

/* Variables and functions */
 int BCS_10 ; 
 int BCS_12 ; 
 int BCS_16 ; 
 int BCS_6 ; 
 int BCS_8 ; 
 int /*<<< orphan*/  BND_HSYNC2VSYNC ; 
 int /*<<< orphan*/  DP_BYTE_COUNT ; 
 int /*<<< orphan*/  DP_FRAMER_PXL_REPR ; 
 int /*<<< orphan*/  DP_FRAMER_SP ; 
 int DP_FRAMER_SP_HSP ; 
 int DP_FRAMER_SP_VSP ; 
 int /*<<< orphan*/  DP_FRAMER_TU ; 
 int /*<<< orphan*/  DP_FRONT_BACK_PORCH ; 
 int /*<<< orphan*/  DP_HORIZONTAL ; 
 int /*<<< orphan*/  DP_VB_ID ; 
 int /*<<< orphan*/  DP_VC_TABLE (int) ; 
 int /*<<< orphan*/  DP_VERTICAL_0 ; 
 int /*<<< orphan*/  DP_VERTICAL_1 ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HSYNC2VSYNC_POL_CTRL ; 
 int /*<<< orphan*/  MSA_HORIZONTAL_0 ; 
 int /*<<< orphan*/  MSA_HORIZONTAL_1 ; 
 int /*<<< orphan*/  MSA_MISC ; 
 int /*<<< orphan*/  MSA_VERTICAL_0 ; 
 int /*<<< orphan*/  MSA_VERTICAL_1 ; 
 int /*<<< orphan*/  STREAM_CONFIG ; 
 int TU_CNT_RST_EN ; 
 int TU_SIZE ; 
 int VIF_BYPASS_INTERLACE ; 
 int YCBCR_4_2_2 ; 
 int cdn_dp_get_msa_misc (struct video_info*,struct drm_display_mode*) ; 
 int cdn_dp_reg_write (struct cdn_dp_device*,int /*<<< orphan*/ ,int) ; 
 int cdn_dp_reg_write_bit (struct cdn_dp_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int div_u64 (int,int) ; 
 int do_div (int,int) ; 

int cdn_dp_config_video(struct cdn_dp_device *dp)
{
	struct video_info *video = &dp->video_info;
	struct drm_display_mode *mode = &dp->mode;
	u64 symbol;
	u32 val, link_rate, rem;
	u8 bit_per_pix, tu_size_reg = TU_SIZE;
	int ret;

	bit_per_pix = (video->color_fmt == YCBCR_4_2_2) ?
		      (video->color_depth * 2) : (video->color_depth * 3);

	link_rate = dp->link.rate / 1000;

	ret = cdn_dp_reg_write(dp, BND_HSYNC2VSYNC, VIF_BYPASS_INTERLACE);
	if (ret)
		goto err_config_video;

	ret = cdn_dp_reg_write(dp, HSYNC2VSYNC_POL_CTRL, 0);
	if (ret)
		goto err_config_video;

	/*
	 * get a best tu_size and valid symbol:
	 * 1. chose Lclk freq(162Mhz, 270Mhz, 540Mhz), set TU to 32
	 * 2. calculate VS(valid symbol) = TU * Pclk * Bpp / (Lclk * Lanes)
	 * 3. if VS > *.85 or VS < *.1 or VS < 2 or TU < VS + 4, then set
	 *    TU += 2 and repeat 2nd step.
	 */
	do {
		tu_size_reg += 2;
		symbol = tu_size_reg * mode->clock * bit_per_pix;
		do_div(symbol, dp->link.num_lanes * link_rate * 8);
		rem = do_div(symbol, 1000);
		if (tu_size_reg > 64) {
			ret = -EINVAL;
			DRM_DEV_ERROR(dp->dev,
				      "tu error, clk:%d, lanes:%d, rate:%d\n",
				      mode->clock, dp->link.num_lanes,
				      link_rate);
			goto err_config_video;
		}
	} while ((symbol <= 1) || (tu_size_reg - symbol < 4) ||
		 (rem > 850) || (rem < 100));

	val = symbol + (tu_size_reg << 8);
	val |= TU_CNT_RST_EN;
	ret = cdn_dp_reg_write(dp, DP_FRAMER_TU, val);
	if (ret)
		goto err_config_video;

	/* set the FIFO Buffer size */
	val = div_u64(mode->clock * (symbol + 1), 1000) + link_rate;
	val /= (dp->link.num_lanes * link_rate);
	val = div_u64(8 * (symbol + 1), bit_per_pix) - val;
	val += 2;
	ret = cdn_dp_reg_write(dp, DP_VC_TABLE(15), val);

	switch (video->color_depth) {
	case 6:
		val = BCS_6;
		break;
	case 8:
		val = BCS_8;
		break;
	case 10:
		val = BCS_10;
		break;
	case 12:
		val = BCS_12;
		break;
	case 16:
		val = BCS_16;
		break;
	};

	val += video->color_fmt << 8;
	ret = cdn_dp_reg_write(dp, DP_FRAMER_PXL_REPR, val);
	if (ret)
		goto err_config_video;

	val = video->h_sync_polarity ? DP_FRAMER_SP_HSP : 0;
	val |= video->v_sync_polarity ? DP_FRAMER_SP_VSP : 0;
	ret = cdn_dp_reg_write(dp, DP_FRAMER_SP, val);
	if (ret)
		goto err_config_video;

	val = (mode->hsync_start - mode->hdisplay) << 16;
	val |= mode->htotal - mode->hsync_end;
	ret = cdn_dp_reg_write(dp, DP_FRONT_BACK_PORCH, val);
	if (ret)
		goto err_config_video;

	val = mode->hdisplay * bit_per_pix / 8;
	ret = cdn_dp_reg_write(dp, DP_BYTE_COUNT, val);
	if (ret)
		goto err_config_video;

	val = mode->htotal | ((mode->htotal - mode->hsync_start) << 16);
	ret = cdn_dp_reg_write(dp, MSA_HORIZONTAL_0, val);
	if (ret)
		goto err_config_video;

	val = mode->hsync_end - mode->hsync_start;
	val |= (mode->hdisplay << 16) | (video->h_sync_polarity << 15);
	ret = cdn_dp_reg_write(dp, MSA_HORIZONTAL_1, val);
	if (ret)
		goto err_config_video;

	val = mode->vtotal;
	val |= (mode->vtotal - mode->vsync_start) << 16;
	ret = cdn_dp_reg_write(dp, MSA_VERTICAL_0, val);
	if (ret)
		goto err_config_video;

	val = mode->vsync_end - mode->vsync_start;
	val |= (mode->vdisplay << 16) | (video->v_sync_polarity << 15);
	ret = cdn_dp_reg_write(dp, MSA_VERTICAL_1, val);
	if (ret)
		goto err_config_video;

	val = cdn_dp_get_msa_misc(video, mode);
	ret = cdn_dp_reg_write(dp, MSA_MISC, val);
	if (ret)
		goto err_config_video;

	ret = cdn_dp_reg_write(dp, STREAM_CONFIG, 1);
	if (ret)
		goto err_config_video;

	val = mode->hsync_end - mode->hsync_start;
	val |= mode->hdisplay << 16;
	ret = cdn_dp_reg_write(dp, DP_HORIZONTAL, val);
	if (ret)
		goto err_config_video;

	val = mode->vdisplay;
	val |= (mode->vtotal - mode->vsync_start) << 16;
	ret = cdn_dp_reg_write(dp, DP_VERTICAL_0, val);
	if (ret)
		goto err_config_video;

	val = mode->vtotal;
	ret = cdn_dp_reg_write(dp, DP_VERTICAL_1, val);
	if (ret)
		goto err_config_video;

	ret = cdn_dp_reg_write_bit(dp, DP_VB_ID, 2, 1, 0);

err_config_video:
	if (ret)
		DRM_DEV_ERROR(dp->dev, "config video failed: %d\n", ret);
	return ret;
}