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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct platform_device {int dummy; } ;
struct omap_overlay_manager {int dummy; } ;
struct omap_dss_device {struct omap_overlay_manager* manager; } ;
struct TYPE_2__ {int x_res; } ;
struct dsi_data {int pix_fmt; scalar_t__ mode; TYPE_1__ timings; struct omap_dss_device output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MIPI_DSI_PACKED_PIXEL_STREAM_16 ; 
 int /*<<< orphan*/  MIPI_DSI_PACKED_PIXEL_STREAM_18 ; 
 int /*<<< orphan*/  MIPI_DSI_PACKED_PIXEL_STREAM_24 ; 
 int /*<<< orphan*/  MIPI_DSI_PIXEL_STREAM_3BYTE_18 ; 
#define  OMAP_DSS_DSI_FMT_RGB565 131 
#define  OMAP_DSS_DSI_FMT_RGB666 130 
#define  OMAP_DSS_DSI_FMT_RGB666_PACKED 129 
#define  OMAP_DSS_DSI_FMT_RGB888 128 
 scalar_t__ OMAP_DSS_DSI_VIDEO_MODE ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct platform_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int dsi_display_init_dispc (struct platform_device*,struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dsi_display_uninit_dispc (struct platform_device*,struct omap_overlay_manager*) ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int dsi_get_pixel_size (int) ; 
 int /*<<< orphan*/  dsi_if_enable (struct platform_device*,int) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct platform_device*,int,int) ; 
 int /*<<< orphan*/  dsi_vc_write_long_header (struct platform_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dss_mgr_enable (struct omap_overlay_manager*) ; 

__attribute__((used)) static int dsi_enable_video_output(struct omap_dss_device *dssdev, int channel)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	struct omap_overlay_manager *mgr = dsi->output.manager;
	int bpp = dsi_get_pixel_size(dsi->pix_fmt);
	struct omap_dss_device *out = &dsi->output;
	u8 data_type;
	u16 word_count;
	int r;

	if (out->manager == NULL) {
		DSSERR("failed to enable display: no output/manager\n");
		return -ENODEV;
	}

	r = dsi_display_init_dispc(dsidev, mgr);
	if (r)
		goto err_init_dispc;

	if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		switch (dsi->pix_fmt) {
		case OMAP_DSS_DSI_FMT_RGB888:
			data_type = MIPI_DSI_PACKED_PIXEL_STREAM_24;
			break;
		case OMAP_DSS_DSI_FMT_RGB666:
			data_type = MIPI_DSI_PIXEL_STREAM_3BYTE_18;
			break;
		case OMAP_DSS_DSI_FMT_RGB666_PACKED:
			data_type = MIPI_DSI_PACKED_PIXEL_STREAM_18;
			break;
		case OMAP_DSS_DSI_FMT_RGB565:
			data_type = MIPI_DSI_PACKED_PIXEL_STREAM_16;
			break;
		default:
			r = -EINVAL;
			goto err_pix_fmt;
		}

		dsi_if_enable(dsidev, false);
		dsi_vc_enable(dsidev, channel, false);

		/* MODE, 1 = video mode */
		REG_FLD_MOD(dsidev, DSI_VC_CTRL(channel), 1, 4, 4);

		word_count = DIV_ROUND_UP(dsi->timings.x_res * bpp, 8);

		dsi_vc_write_long_header(dsidev, channel, data_type,
				word_count, 0);

		dsi_vc_enable(dsidev, channel, true);
		dsi_if_enable(dsidev, true);
	}

	r = dss_mgr_enable(mgr);
	if (r)
		goto err_mgr_enable;

	return 0;

err_mgr_enable:
	if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		dsi_if_enable(dsidev, false);
		dsi_vc_enable(dsidev, channel, false);
	}
err_pix_fmt:
	dsi_display_uninit_dispc(dsidev, mgr);
err_init_dispc:
	return r;
}