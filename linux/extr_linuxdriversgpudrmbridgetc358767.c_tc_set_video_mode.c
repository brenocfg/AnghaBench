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
struct tc_data {int /*<<< orphan*/  dev; } ;
struct drm_display_mode {int htotal; int hsync_end; int hsync_start; int hdisplay; int vtotal; int vsync_end; int vsync_start; int vdisplay; int flags; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int BPC_8 ; 
 int DE_POL_ACTIVE_HIGH ; 
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
 int FRMSYNC_DISABLED ; 
 int HS_POL_ACTIVE_LOW ; 
 int /*<<< orphan*/  HTIM01 ; 
 int /*<<< orphan*/  HTIM02 ; 
 int MSF_DISABLED ; 
 int OPXLFMT_RGB888 ; 
 int SUB_CFG_TYPE_CONFIG1 ; 
 int SYNCVAL_HS_POL_ACTIVE_LOW ; 
 int SYNCVAL_VS_POL_ACTIVE_LOW ; 
 int /*<<< orphan*/  TSTCTL ; 
 int TU_SIZE_RECOMMENDED ; 
 int VFUEN ; 
 int /*<<< orphan*/  VFUEN0 ; 
 int /*<<< orphan*/  VPCTRL0 ; 
 int VS_POL_ACTIVE_LOW ; 
 int /*<<< orphan*/  VTIM01 ; 
 int /*<<< orphan*/  VTIM02 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  tc_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tc_set_video_mode(struct tc_data *tc, struct drm_display_mode *mode)
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

	/*
	 * Recommended maximum number of symbols transferred in a transfer unit:
	 * DIV_ROUND_UP((input active video bandwidth in bytes) * tu_size,
	 *              (output active video bandwidth in bytes))
	 * Must be less than tu_size.
	 */
	max_tu_symbol = TU_SIZE_RECOMMENDED - 1;

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
	tc_write(VPCTRL0, (0 << 20) /* VSDELAY */ |
		 OPXLFMT_RGB888 | FRMSYNC_DISABLED | MSF_DISABLED);
	tc_write(HTIM01, (ALIGN(left_margin, 2) << 16) | /* H back porch */
			 (ALIGN(hsync_len, 2) << 0));	 /* Hsync */
	tc_write(HTIM02, (ALIGN(right_margin, 2) << 16) |  /* H front porch */
			 (ALIGN(mode->hdisplay, 2) << 0)); /* width */
	tc_write(VTIM01, (upper_margin << 16) |		/* V back porch */
			 (vsync_len << 0));		/* Vsync */
	tc_write(VTIM02, (lower_margin << 16) |		/* V front porch */
			 (mode->vdisplay << 0));	/* height */
	tc_write(VFUEN0, VFUEN);		/* update settings */

	/* Test pattern settings */
	tc_write(TSTCTL,
		 (120 << 24) |	/* Red Color component value */
		 (20 << 16) |	/* Green Color component value */
		 (99 << 8) |	/* Blue Color component value */
		 (1 << 4) |	/* Enable I2C Filter */
		 (2 << 0) |	/* Color bar Mode */
		 0);

	/* DP Main Stream Attributes */
	vid_sync_dly = hsync_len + left_margin + mode->hdisplay;
	tc_write(DP0_VIDSYNCDELAY,
		 (max_tu_symbol << 16) |	/* thresh_dly */
		 (vid_sync_dly << 0));

	tc_write(DP0_TOTALVAL, (mode->vtotal << 16) | (mode->htotal));

	tc_write(DP0_STARTVAL,
		 ((upper_margin + vsync_len) << 16) |
		 ((left_margin + hsync_len) << 0));

	tc_write(DP0_ACTIVEVAL, (mode->vdisplay << 16) | (mode->hdisplay));

	tc_write(DP0_SYNCVAL, (vsync_len << 16) | (hsync_len << 0) |
		 ((mode->flags & DRM_MODE_FLAG_NHSYNC) ? SYNCVAL_HS_POL_ACTIVE_LOW : 0) |
		 ((mode->flags & DRM_MODE_FLAG_NVSYNC) ? SYNCVAL_VS_POL_ACTIVE_LOW : 0));

	tc_write(DPIPXLFMT, VS_POL_ACTIVE_LOW | HS_POL_ACTIVE_LOW |
		 DE_POL_ACTIVE_HIGH | SUB_CFG_TYPE_CONFIG1 | DPI_BPP_RGB888);

	tc_write(DP0_MISC, (max_tu_symbol << 23) | (TU_SIZE_RECOMMENDED << 16) |
			   BPC_8);

	return 0;
err:
	return ret;
}