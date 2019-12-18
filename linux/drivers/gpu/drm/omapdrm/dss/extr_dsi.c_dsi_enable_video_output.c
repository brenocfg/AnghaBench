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
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {int hactive; } ;
struct dsi_data {int pix_fmt; scalar_t__ mode; int /*<<< orphan*/  output; TYPE_1__ vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MIPI_DSI_PACKED_PIXEL_STREAM_16 ; 
 int /*<<< orphan*/  MIPI_DSI_PACKED_PIXEL_STREAM_18 ; 
 int /*<<< orphan*/  MIPI_DSI_PACKED_PIXEL_STREAM_24 ; 
 int /*<<< orphan*/  MIPI_DSI_PIXEL_STREAM_3BYTE_18 ; 
#define  OMAP_DSS_DSI_FMT_RGB565 131 
#define  OMAP_DSS_DSI_FMT_RGB666 130 
#define  OMAP_DSS_DSI_FMT_RGB666_PACKED 129 
#define  OMAP_DSS_DSI_FMT_RGB888 128 
 scalar_t__ OMAP_DSS_DSI_VIDEO_MODE ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int,int,int) ; 
 int dsi_display_init_dispc (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_display_uninit_dispc (struct dsi_data*) ; 
 int dsi_get_pixel_size (int) ; 
 int /*<<< orphan*/  dsi_if_enable (struct dsi_data*,int) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct dsi_data*,int,int) ; 
 int /*<<< orphan*/  dsi_vc_write_long_header (struct dsi_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dss_mgr_enable (int /*<<< orphan*/ *) ; 
 struct dsi_data* to_dsi_data (struct omap_dss_device*) ; 

__attribute__((used)) static int dsi_enable_video_output(struct omap_dss_device *dssdev, int channel)
{
	struct dsi_data *dsi = to_dsi_data(dssdev);
	int bpp = dsi_get_pixel_size(dsi->pix_fmt);
	u8 data_type;
	u16 word_count;
	int r;

	r = dsi_display_init_dispc(dsi);
	if (r)
		return r;

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

		dsi_if_enable(dsi, false);
		dsi_vc_enable(dsi, channel, false);

		/* MODE, 1 = video mode */
		REG_FLD_MOD(dsi, DSI_VC_CTRL(channel), 1, 4, 4);

		word_count = DIV_ROUND_UP(dsi->vm.hactive * bpp, 8);

		dsi_vc_write_long_header(dsi, channel, data_type,
				word_count, 0);

		dsi_vc_enable(dsi, channel, true);
		dsi_if_enable(dsi, true);
	}

	r = dss_mgr_enable(&dsi->output);
	if (r)
		goto err_mgr_enable;

	return 0;

err_mgr_enable:
	if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		dsi_if_enable(dsi, false);
		dsi_vc_enable(dsi, channel, false);
	}
err_pix_fmt:
	dsi_display_uninit_dispc(dsi);
	return r;
}