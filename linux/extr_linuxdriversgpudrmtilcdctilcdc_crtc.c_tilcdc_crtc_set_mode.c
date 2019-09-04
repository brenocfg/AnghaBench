#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct tilcdc_panel_info {int dma_burst_sz; int fifo_th; int fdd; scalar_t__ raster_order; scalar_t__ sync_edge; scalar_t__ sync_ctrl; scalar_t__ invert_pxl_clk; scalar_t__ tft_alt_mode; int /*<<< orphan*/  ac_bias_intrpt; int /*<<< orphan*/  ac_bias; } ;
struct tilcdc_drm_private {int rev; } ;
struct tilcdc_crtc {int /*<<< orphan*/  hvtotal_us; struct tilcdc_panel_info* info; } ;
struct drm_framebuffer {TYPE_4__* format; } ;
struct drm_display_mode {int htotal; int hsync_end; int hsync_start; int hdisplay; int vtotal; int vsync_end; int vsync_start; int vdisplay; int flags; } ;
struct drm_device {int /*<<< orphan*/  dev; struct tilcdc_drm_private* dev_private; } ;
struct drm_crtc {struct drm_display_mode hwmode; TYPE_1__* state; TYPE_3__* primary; struct drm_device* dev; } ;
struct TYPE_8__ {int format; } ;
struct TYPE_7__ {TYPE_2__* state; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;
struct TYPE_5__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int,int,int,int,int,int,int) ; 
#define  DRM_FORMAT_BGR565 133 
#define  DRM_FORMAT_BGR888 132 
#define  DRM_FORMAT_RGB565 131 
#define  DRM_FORMAT_RGB888 130 
#define  DRM_FORMAT_XBGR8888 129 
#define  DRM_FORMAT_XRGB8888 128 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int LCDC_AC_BIAS_FREQUENCY (int /*<<< orphan*/ ) ; 
 int LCDC_AC_BIAS_TRANSITIONS_PER_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCDC_DMA_BURST_1 ; 
 int /*<<< orphan*/  LCDC_DMA_BURST_16 ; 
 int /*<<< orphan*/  LCDC_DMA_BURST_2 ; 
 int /*<<< orphan*/  LCDC_DMA_BURST_4 ; 
 int /*<<< orphan*/  LCDC_DMA_BURST_8 ; 
 int LCDC_DMA_BURST_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCDC_DMA_CTRL_REG ; 
 int /*<<< orphan*/  LCDC_INVERT_HSYNC ; 
 int /*<<< orphan*/  LCDC_INVERT_PIXEL_CLOCK ; 
 int /*<<< orphan*/  LCDC_INVERT_VSYNC ; 
 int /*<<< orphan*/  LCDC_LPP_B10 ; 
 int LCDC_MONOCHROME_MODE ; 
 int LCDC_MONO_8BIT_MODE ; 
 int /*<<< orphan*/  LCDC_RASTER_CTRL_REG ; 
 int /*<<< orphan*/  LCDC_RASTER_ORDER ; 
 int /*<<< orphan*/  LCDC_RASTER_TIMING_0_REG ; 
 int /*<<< orphan*/  LCDC_RASTER_TIMING_1_REG ; 
 int /*<<< orphan*/  LCDC_RASTER_TIMING_2_REG ; 
 int /*<<< orphan*/  LCDC_SYNC_CTRL ; 
 int /*<<< orphan*/  LCDC_SYNC_EDGE ; 
 int LCDC_TFT_ALT_ENABLE ; 
 int LCDC_TFT_MODE ; 
 int LCDC_V2_TFT_24BPP_MODE ; 
 int LCDC_V2_TFT_24BPP_UNPACK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_scanout (struct drm_crtc*,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  tilcdc_clear (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_crtc_load_palette (struct drm_crtc*) ; 
 int /*<<< orphan*/  tilcdc_crtc_set_clk (struct drm_crtc*) ; 
 int /*<<< orphan*/  tilcdc_mode_hvtotal (struct drm_display_mode*) ; 
 int tilcdc_read (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_set (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_write (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 struct tilcdc_crtc* to_tilcdc_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void tilcdc_crtc_set_mode(struct drm_crtc *crtc)
{
	struct tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct tilcdc_drm_private *priv = dev->dev_private;
	const struct tilcdc_panel_info *info = tilcdc_crtc->info;
	uint32_t reg, hbp, hfp, hsw, vbp, vfp, vsw;
	struct drm_display_mode *mode = &crtc->state->adjusted_mode;
	struct drm_framebuffer *fb = crtc->primary->state->fb;

	if (WARN_ON(!info))
		return;

	if (WARN_ON(!fb))
		return;

	/* Configure the Burst Size and fifo threshold of DMA: */
	reg = tilcdc_read(dev, LCDC_DMA_CTRL_REG) & ~0x00000770;
	switch (info->dma_burst_sz) {
	case 1:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_1);
		break;
	case 2:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_2);
		break;
	case 4:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_4);
		break;
	case 8:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_8);
		break;
	case 16:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_16);
		break;
	default:
		dev_err(dev->dev, "invalid burst size\n");
		return;
	}
	reg |= (info->fifo_th << 8);
	tilcdc_write(dev, LCDC_DMA_CTRL_REG, reg);

	/* Configure timings: */
	hbp = mode->htotal - mode->hsync_end;
	hfp = mode->hsync_start - mode->hdisplay;
	hsw = mode->hsync_end - mode->hsync_start;
	vbp = mode->vtotal - mode->vsync_end;
	vfp = mode->vsync_start - mode->vdisplay;
	vsw = mode->vsync_end - mode->vsync_start;

	DBG("%dx%d, hbp=%u, hfp=%u, hsw=%u, vbp=%u, vfp=%u, vsw=%u",
	    mode->hdisplay, mode->vdisplay, hbp, hfp, hsw, vbp, vfp, vsw);

	/* Set AC Bias Period and Number of Transitions per Interrupt: */
	reg = tilcdc_read(dev, LCDC_RASTER_TIMING_2_REG) & ~0x000fff00;
	reg |= LCDC_AC_BIAS_FREQUENCY(info->ac_bias) |
		LCDC_AC_BIAS_TRANSITIONS_PER_INT(info->ac_bias_intrpt);

	/*
	 * subtract one from hfp, hbp, hsw because the hardware uses
	 * a value of 0 as 1
	 */
	if (priv->rev == 2) {
		/* clear bits we're going to set */
		reg &= ~0x78000033;
		reg |= ((hfp-1) & 0x300) >> 8;
		reg |= ((hbp-1) & 0x300) >> 4;
		reg |= ((hsw-1) & 0x3c0) << 21;
	}
	tilcdc_write(dev, LCDC_RASTER_TIMING_2_REG, reg);

	reg = (((mode->hdisplay >> 4) - 1) << 4) |
		(((hbp-1) & 0xff) << 24) |
		(((hfp-1) & 0xff) << 16) |
		(((hsw-1) & 0x3f) << 10);
	if (priv->rev == 2)
		reg |= (((mode->hdisplay >> 4) - 1) & 0x40) >> 3;
	tilcdc_write(dev, LCDC_RASTER_TIMING_0_REG, reg);

	reg = ((mode->vdisplay - 1) & 0x3ff) |
		((vbp & 0xff) << 24) |
		((vfp & 0xff) << 16) |
		(((vsw-1) & 0x3f) << 10);
	tilcdc_write(dev, LCDC_RASTER_TIMING_1_REG, reg);

	/*
	 * be sure to set Bit 10 for the V2 LCDC controller,
	 * otherwise limited to 1024 pixels width, stopping
	 * 1920x1080 being supported.
	 */
	if (priv->rev == 2) {
		if ((mode->vdisplay - 1) & 0x400) {
			tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG,
				LCDC_LPP_B10);
		} else {
			tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG,
				LCDC_LPP_B10);
		}
	}

	/* Configure display type: */
	reg = tilcdc_read(dev, LCDC_RASTER_CTRL_REG) &
		~(LCDC_TFT_MODE | LCDC_MONO_8BIT_MODE | LCDC_MONOCHROME_MODE |
		  LCDC_V2_TFT_24BPP_MODE | LCDC_V2_TFT_24BPP_UNPACK |
		  0x000ff000 /* Palette Loading Delay bits */);
	reg |= LCDC_TFT_MODE; /* no monochrome/passive support */
	if (info->tft_alt_mode)
		reg |= LCDC_TFT_ALT_ENABLE;
	if (priv->rev == 2) {
		switch (fb->format->format) {
		case DRM_FORMAT_BGR565:
		case DRM_FORMAT_RGB565:
			break;
		case DRM_FORMAT_XBGR8888:
		case DRM_FORMAT_XRGB8888:
			reg |= LCDC_V2_TFT_24BPP_UNPACK;
			/* fallthrough */
		case DRM_FORMAT_BGR888:
		case DRM_FORMAT_RGB888:
			reg |= LCDC_V2_TFT_24BPP_MODE;
			break;
		default:
			dev_err(dev->dev, "invalid pixel format\n");
			return;
		}
	}
	reg |= info->fdd < 12;
	tilcdc_write(dev, LCDC_RASTER_CTRL_REG, reg);

	if (info->invert_pxl_clk)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_PIXEL_CLOCK);
	else
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_PIXEL_CLOCK);

	if (info->sync_ctrl)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_SYNC_CTRL);
	else
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_SYNC_CTRL);

	if (info->sync_edge)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_SYNC_EDGE);
	else
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_SYNC_EDGE);

	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_HSYNC);
	else
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_HSYNC);

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_VSYNC);
	else
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_VSYNC);

	if (info->raster_order)
		tilcdc_set(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ORDER);
	else
		tilcdc_clear(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ORDER);

	tilcdc_crtc_set_clk(crtc);

	tilcdc_crtc_load_palette(crtc);

	set_scanout(crtc, fb);

	crtc->hwmode = crtc->state->adjusted_mode;

	tilcdc_crtc->hvtotal_us =
		tilcdc_mode_hvtotal(&crtc->hwmode);
}