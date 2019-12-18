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
typedef  int u32 ;
struct TYPE_3__ {int num_lanes; int rate; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct tc_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; TYPE_2__ link; } ;
struct drm_display_mode {int htotal; int hsync_end; int hsync_start; int hdisplay; int vtotal; int vsync_end; int vsync_start; int vdisplay; int clock; int flags; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int BPC_8 ; 
 int /*<<< orphan*/  COLOR_B ; 
 int /*<<< orphan*/  COLOR_BAR_MODE ; 
 int COLOR_BAR_MODE_BARS ; 
 int /*<<< orphan*/  COLOR_G ; 
 int /*<<< orphan*/  COLOR_R ; 
 int DE_POL_ACTIVE_HIGH ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DP0_ACTIVEVAL ; 
 int /*<<< orphan*/  DP0_MISC ; 
 int /*<<< orphan*/  DP0_STARTVAL ; 
 int /*<<< orphan*/  DP0_SYNCVAL ; 
 int /*<<< orphan*/  DP0_TOTALVAL ; 
 int /*<<< orphan*/  DP0_VIDSYNCDELAY ; 
 int /*<<< orphan*/  DPIPXLFMT ; 
 int DPI_BPP_RGB888 ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int ENI2CFILTER ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int FRMSYNC_DISABLED ; 
 int /*<<< orphan*/  HBPR ; 
 int /*<<< orphan*/  HDISPR ; 
 int /*<<< orphan*/  HFPR ; 
 int /*<<< orphan*/  HPW ; 
 int HS_POL_ACTIVE_LOW ; 
 int /*<<< orphan*/  HS_WIDTH ; 
 int /*<<< orphan*/  HTIM01 ; 
 int /*<<< orphan*/  HTIM02 ; 
 int /*<<< orphan*/  H_ACT ; 
 int /*<<< orphan*/  H_START ; 
 int /*<<< orphan*/  H_TOTAL ; 
 int /*<<< orphan*/  MAX_TU_SYMBOL ; 
 int MSF_DISABLED ; 
 int OPXLFMT_RGB888 ; 
 int SUB_CFG_TYPE_CONFIG1 ; 
 int SYNCVAL_HS_POL_ACTIVE_LOW ; 
 int SYNCVAL_VS_POL_ACTIVE_LOW ; 
 int /*<<< orphan*/  THRESH_DLY ; 
 int /*<<< orphan*/  TSTCTL ; 
 int /*<<< orphan*/  TU_SIZE ; 
 int TU_SIZE_RECOMMENDED ; 
 int /*<<< orphan*/  VBPR ; 
 int /*<<< orphan*/  VDISPR ; 
 int /*<<< orphan*/  VFPR ; 
 int VFUEN ; 
 int /*<<< orphan*/  VFUEN0 ; 
 int /*<<< orphan*/  VID_SYNC_DLY ; 
 int /*<<< orphan*/  VPCTRL0 ; 
 int /*<<< orphan*/  VSDELAY ; 
 int /*<<< orphan*/  VSPR ; 
 int VS_POL_ACTIVE_LOW ; 
 int /*<<< orphan*/  VS_WIDTH ; 
 int /*<<< orphan*/  VTIM01 ; 
 int /*<<< orphan*/  VTIM02 ; 
 int /*<<< orphan*/  V_ACT ; 
 int /*<<< orphan*/  V_START ; 
 int /*<<< orphan*/  V_TOTAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tc_set_video_mode(struct tc_data *tc,
			     const struct drm_display_mode *mode)
{
	int ret;
	int vid_sync_dly;
	int max_tu_symbol;

	int left_margin = mode->htotal - mode->hsync_end;
	int right_margin = mode->hsync_start - mode->hdisplay;
	int hsync_len = mode->hsync_end - mode->hsync_start;
	int upper_margin = mode->vtotal - mode->vsync_end;
	int lower_margin = mode->vsync_start - mode->vdisplay;
	int vsync_len = mode->vsync_end - mode->vsync_start;
	u32 dp0_syncval;
	u32 bits_per_pixel = 24;
	u32 in_bw, out_bw;

	/*
	 * Recommended maximum number of symbols transferred in a transfer unit:
	 * DIV_ROUND_UP((input active video bandwidth in bytes) * tu_size,
	 *              (output active video bandwidth in bytes))
	 * Must be less than tu_size.
	 */

	in_bw = mode->clock * bits_per_pixel / 8;
	out_bw = tc->link.base.num_lanes * tc->link.base.rate;
	max_tu_symbol = DIV_ROUND_UP(in_bw * TU_SIZE_RECOMMENDED, out_bw);

	dev_dbg(tc->dev, "set mode %dx%d\n",
		mode->hdisplay, mode->vdisplay);
	dev_dbg(tc->dev, "H margin %d,%d sync %d\n",
		left_margin, right_margin, hsync_len);
	dev_dbg(tc->dev, "V margin %d,%d sync %d\n",
		upper_margin, lower_margin, vsync_len);
	dev_dbg(tc->dev, "total: %dx%d\n", mode->htotal, mode->vtotal);


	/*
	 * LCD Ctl Frame Size
	 * datasheet is not clear of vsdelay in case of DPI
	 * assume we do not need any delay when DPI is a source of
	 * sync signals
	 */
	ret = regmap_write(tc->regmap, VPCTRL0,
			   FIELD_PREP(VSDELAY, 0) |
			   OPXLFMT_RGB888 | FRMSYNC_DISABLED | MSF_DISABLED);
	if (ret)
		return ret;

	ret = regmap_write(tc->regmap, HTIM01,
			   FIELD_PREP(HBPR, ALIGN(left_margin, 2)) |
			   FIELD_PREP(HPW, ALIGN(hsync_len, 2)));
	if (ret)
		return ret;

	ret = regmap_write(tc->regmap, HTIM02,
			   FIELD_PREP(HDISPR, ALIGN(mode->hdisplay, 2)) |
			   FIELD_PREP(HFPR, ALIGN(right_margin, 2)));
	if (ret)
		return ret;

	ret = regmap_write(tc->regmap, VTIM01,
			   FIELD_PREP(VBPR, upper_margin) |
			   FIELD_PREP(VSPR, vsync_len));
	if (ret)
		return ret;

	ret = regmap_write(tc->regmap, VTIM02,
			   FIELD_PREP(VFPR, lower_margin) |
			   FIELD_PREP(VDISPR, mode->vdisplay));
	if (ret)
		return ret;

	ret = regmap_write(tc->regmap, VFUEN0, VFUEN); /* update settings */
	if (ret)
		return ret;

	/* Test pattern settings */
	ret = regmap_write(tc->regmap, TSTCTL,
			   FIELD_PREP(COLOR_R, 120) |
			   FIELD_PREP(COLOR_G, 20) |
			   FIELD_PREP(COLOR_B, 99) |
			   ENI2CFILTER |
			   FIELD_PREP(COLOR_BAR_MODE, COLOR_BAR_MODE_BARS));
	if (ret)
		return ret;

	/* DP Main Stream Attributes */
	vid_sync_dly = hsync_len + left_margin + mode->hdisplay;
	ret = regmap_write(tc->regmap, DP0_VIDSYNCDELAY,
		 FIELD_PREP(THRESH_DLY, max_tu_symbol) |
		 FIELD_PREP(VID_SYNC_DLY, vid_sync_dly));

	ret = regmap_write(tc->regmap, DP0_TOTALVAL,
			   FIELD_PREP(H_TOTAL, mode->htotal) |
			   FIELD_PREP(V_TOTAL, mode->vtotal));
	if (ret)
		return ret;

	ret = regmap_write(tc->regmap, DP0_STARTVAL,
			   FIELD_PREP(H_START, left_margin + hsync_len) |
			   FIELD_PREP(V_START, upper_margin + vsync_len));
	if (ret)
		return ret;

	ret = regmap_write(tc->regmap, DP0_ACTIVEVAL,
			   FIELD_PREP(V_ACT, mode->vdisplay) |
			   FIELD_PREP(H_ACT, mode->hdisplay));
	if (ret)
		return ret;

	dp0_syncval = FIELD_PREP(VS_WIDTH, vsync_len) |
		      FIELD_PREP(HS_WIDTH, hsync_len);

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		dp0_syncval |= SYNCVAL_VS_POL_ACTIVE_LOW;

	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		dp0_syncval |= SYNCVAL_HS_POL_ACTIVE_LOW;

	ret = regmap_write(tc->regmap, DP0_SYNCVAL, dp0_syncval);
	if (ret)
		return ret;

	ret = regmap_write(tc->regmap, DPIPXLFMT,
			   VS_POL_ACTIVE_LOW | HS_POL_ACTIVE_LOW |
			   DE_POL_ACTIVE_HIGH | SUB_CFG_TYPE_CONFIG1 |
			   DPI_BPP_RGB888);
	if (ret)
		return ret;

	ret = regmap_write(tc->regmap, DP0_MISC,
			   FIELD_PREP(MAX_TU_SYMBOL, max_tu_symbol) |
			   FIELD_PREP(TU_SIZE, TU_SIZE_RECOMMENDED) |
			   BPC_8);
	if (ret)
		return ret;

	return 0;
}