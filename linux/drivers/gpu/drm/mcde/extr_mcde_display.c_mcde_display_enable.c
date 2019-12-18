#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mcde {int stride; scalar_t__ regs; scalar_t__ te_sync; TYPE_3__* mdsi; } ;
struct drm_plane {TYPE_1__* state; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_simple_display_pipe {struct drm_plane plane; struct drm_crtc crtc; } ;
struct drm_plane_state {int dummy; } ;
struct drm_framebuffer {TYPE_2__* format; } ;
struct drm_format_name_buf {int dummy; } ;
struct drm_display_mode {int hdisplay; int vdisplay; int flags; } ;
struct drm_device {int /*<<< orphan*/  dev; struct mcde* dev_private; } ;
struct drm_crtc_state {struct drm_display_mode mode; } ;
struct TYPE_6__ {int mode_flags; int /*<<< orphan*/  format; } ;
struct TYPE_5__ {int format; int* cpp; } ;
struct TYPE_4__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_NVSYNC ; 
 int /*<<< orphan*/  MCDE_CHANNEL_0 ; 
 scalar_t__ MCDE_CRC ; 
 int MCDE_CRC_SYCEN0 ; 
 int /*<<< orphan*/  MCDE_DSI_FORMATTER_0 ; 
 int /*<<< orphan*/  MCDE_EXTSRC_0 ; 
 int /*<<< orphan*/  MCDE_FIFO_A ; 
 int /*<<< orphan*/  MCDE_OVERLAY_0 ; 
 scalar_t__ MCDE_VSCRC0 ; 
 int MCDE_VSCRC_VSPOL ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_get_format_name (int,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  mcde_configure_channel (struct mcde*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  mcde_configure_dsi_formatter (struct mcde*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mcde_configure_extsrc (struct mcde*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcde_configure_fifo (struct mcde*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcde_configure_overlay (struct mcde*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_display_mode const*,int) ; 
 int /*<<< orphan*/  mcde_drain_pipe (struct mcde*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mcde_dsi_get_pkt_div (int,int) ; 
 int min (int,int) ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mcde_display_enable(struct drm_simple_display_pipe *pipe,
				struct drm_crtc_state *cstate,
				struct drm_plane_state *plane_state)
{
	struct drm_crtc *crtc = &pipe->crtc;
	struct drm_plane *plane = &pipe->plane;
	struct drm_device *drm = crtc->dev;
	struct mcde *mcde = drm->dev_private;
	const struct drm_display_mode *mode = &cstate->mode;
	struct drm_framebuffer *fb = plane->state->fb;
	u32 format = fb->format->format;
	u32 formatter_ppl = mode->hdisplay; /* pixels per line */
	u32 formatter_lpf = mode->vdisplay; /* lines per frame */
	int pkt_size, fifo_wtrmrk;
	int cpp = fb->format->cpp[0];
	int formatter_cpp;
	struct drm_format_name_buf tmp;
	u32 formatter_frame;
	u32 pkt_div;
	u32 val;

	dev_info(drm->dev, "enable MCDE, %d x %d format %s\n",
		 mode->hdisplay, mode->vdisplay,
		 drm_get_format_name(format, &tmp));
	if (!mcde->mdsi) {
		/* TODO: deal with this for non-DSI output */
		dev_err(drm->dev, "no DSI master attached!\n");
		return;
	}

	dev_info(drm->dev, "output in %s mode, format %dbpp\n",
		 (mcde->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) ?
		 "VIDEO" : "CMD",
		 mipi_dsi_pixel_format_to_bpp(mcde->mdsi->format));
	formatter_cpp =
		mipi_dsi_pixel_format_to_bpp(mcde->mdsi->format) / 8;
	dev_info(drm->dev, "overlay CPP %d bytes, DSI CPP %d bytes\n",
		 cpp,
		 formatter_cpp);

	/* Calculations from mcde_fmtr_dsi.c, fmtr_dsi_enable_video() */

	/*
	 * Set up FIFO A watermark level:
	 * 128 for LCD 32bpp video mode
	 * 48  for LCD 32bpp command mode
	 * 128 for LCD 16bpp video mode
	 * 64  for LCD 16bpp command mode
	 * 128 for HDMI 32bpp
	 * 192 for HDMI 16bpp
	 */
	fifo_wtrmrk = mode->hdisplay;
	if (mcde->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) {
		fifo_wtrmrk = min(fifo_wtrmrk, 128);
		pkt_div = 1;
	} else {
		fifo_wtrmrk = min(fifo_wtrmrk, 48);
		/* The FIFO is 640 entries deep on this v3 hardware */
		pkt_div = mcde_dsi_get_pkt_div(mode->hdisplay, 640);
	}
	dev_dbg(drm->dev, "FIFO watermark after flooring: %d bytes\n",
		fifo_wtrmrk);
	dev_dbg(drm->dev, "Packet divisor: %d bytes\n", pkt_div);

	/* NOTE: pkt_div is 1 for video mode */
	pkt_size = (formatter_ppl * formatter_cpp) / pkt_div;
	/* Commands CMD8 need one extra byte */
	if (!(mcde->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO))
		pkt_size++;

	dev_dbg(drm->dev, "DSI packet size: %d * %d bytes per line\n",
		pkt_size, pkt_div);
	dev_dbg(drm->dev, "Overlay frame size: %u bytes\n",
		mode->hdisplay * mode->vdisplay * cpp);
	mcde->stride = mode->hdisplay * cpp;
	dev_dbg(drm->dev, "Overlay line stride: %u bytes\n",
		mcde->stride);
	/* NOTE: pkt_div is 1 for video mode */
	formatter_frame = pkt_size * pkt_div * formatter_lpf;
	dev_dbg(drm->dev, "Formatter frame size: %u bytes\n", formatter_frame);

	/* Drain the FIFO A + channel 0 pipe so we have a clean slate */
	mcde_drain_pipe(mcde, MCDE_FIFO_A, MCDE_CHANNEL_0);

	/*
	 * We set up our display pipeline:
	 * EXTSRC 0 -> OVERLAY 0 -> CHANNEL 0 -> FIFO A -> DSI FORMATTER 0
	 *
	 * First configure the external source (memory) on external source 0
	 * using the desired bitstream/bitmap format
	 */
	mcde_configure_extsrc(mcde, MCDE_EXTSRC_0, format);

	/*
	 * Configure overlay 0 according to format and mode and take input
	 * from external source 0 and route the output of this overlay to
	 * channel 0
	 */
	mcde_configure_overlay(mcde, MCDE_OVERLAY_0, MCDE_EXTSRC_0,
			       MCDE_CHANNEL_0, mode, format);

	/*
	 * Configure pixel-per-line and line-per-frame for channel 0 and then
	 * route channel 0 to FIFO A
	 */
	mcde_configure_channel(mcde, MCDE_CHANNEL_0, MCDE_FIFO_A, mode);

	/* Configure FIFO A to use DSI formatter 0 */
	mcde_configure_fifo(mcde, MCDE_FIFO_A, MCDE_DSI_FORMATTER_0,
			    fifo_wtrmrk);

	/* Configure the DSI formatter 0 for the DSI panel output */
	mcde_configure_dsi_formatter(mcde, MCDE_DSI_FORMATTER_0,
				     formatter_frame, pkt_size);

	if (mcde->te_sync) {
		if (mode->flags & DRM_MODE_FLAG_NVSYNC)
			val = MCDE_VSCRC_VSPOL;
		else
			val = 0;
		writel(val, mcde->regs + MCDE_VSCRC0);
		/* Enable VSYNC capture on TE0 */
		val = readl(mcde->regs + MCDE_CRC);
		val |= MCDE_CRC_SYCEN0;
		writel(val, mcde->regs + MCDE_CRC);

		drm_crtc_vblank_on(crtc);
	}

	dev_info(drm->dev, "MCDE display is enabled\n");
}