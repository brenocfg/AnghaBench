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
struct TYPE_6__ {int bus_flags; } ;
struct drm_connector {TYPE_3__ display_info; } ;
struct TYPE_4__ {struct drm_connector base; } ;
struct fsl_dcu_drm_device {int /*<<< orphan*/  regmap; int /*<<< orphan*/  pix_clk; TYPE_1__ connector; } ;
struct drm_display_mode {int clock; unsigned int htotal; unsigned int hsync_end; unsigned int hsync_start; unsigned int hdisplay; unsigned int vtotal; unsigned int vsync_end; unsigned int vsync_start; unsigned int vdisplay; int flags; } ;
struct drm_device {struct fsl_dcu_drm_device* dev_private; } ;
struct drm_crtc {TYPE_2__* state; struct drm_device* dev; } ;
struct TYPE_5__ {struct drm_display_mode mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BF_VS_VAL ; 
 int /*<<< orphan*/  BUF_MAX_VAL ; 
 int /*<<< orphan*/  BUF_MIN_VAL ; 
 int /*<<< orphan*/  DCU_BGND ; 
 unsigned int DCU_BGND_B (int /*<<< orphan*/ ) ; 
 unsigned int DCU_BGND_G (int /*<<< orphan*/ ) ; 
 unsigned int DCU_BGND_R (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCU_DCU_MODE ; 
 int /*<<< orphan*/  DCU_DISP_SIZE ; 
 unsigned int DCU_DISP_SIZE_DELTA_X (unsigned int) ; 
 unsigned int DCU_DISP_SIZE_DELTA_Y (unsigned int) ; 
 int /*<<< orphan*/  DCU_HSYN_PARA ; 
 unsigned int DCU_HSYN_PARA_BP (unsigned int) ; 
 unsigned int DCU_HSYN_PARA_FP (unsigned int) ; 
 unsigned int DCU_HSYN_PARA_PW (unsigned int) ; 
 unsigned int DCU_MODE_BLEND_ITER (int) ; 
 unsigned int DCU_MODE_RASTER_EN ; 
 int /*<<< orphan*/  DCU_SYN_POL ; 
 unsigned int DCU_SYN_POL_INV_HS_LOW ; 
 unsigned int DCU_SYN_POL_INV_PXCK ; 
 unsigned int DCU_SYN_POL_INV_VS_LOW ; 
 int /*<<< orphan*/  DCU_THRESHOLD ; 
 unsigned int DCU_THRESHOLD_LS_BF_VS (int /*<<< orphan*/ ) ; 
 unsigned int DCU_THRESHOLD_OUT_BUF_HIGH (int /*<<< orphan*/ ) ; 
 unsigned int DCU_THRESHOLD_OUT_BUF_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCU_VSYN_PARA ; 
 unsigned int DCU_VSYN_PARA_BP (unsigned int) ; 
 unsigned int DCU_VSYN_PARA_FP (unsigned int) ; 
 unsigned int DCU_VSYN_PARA_PW (unsigned int) ; 
 int DRM_BUS_FLAG_PIXDATA_POSEDGE ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 unsigned int drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void fsl_dcu_drm_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct fsl_dcu_drm_device *fsl_dev = dev->dev_private;
	struct drm_connector *con = &fsl_dev->connector.base;
	struct drm_display_mode *mode = &crtc->state->mode;
	unsigned int hbp, hfp, hsw, vbp, vfp, vsw, index, pol = 0;

	index = drm_crtc_index(crtc);
	clk_set_rate(fsl_dev->pix_clk, mode->clock * 1000);

	/* Configure timings: */
	hbp = mode->htotal - mode->hsync_end;
	hfp = mode->hsync_start - mode->hdisplay;
	hsw = mode->hsync_end - mode->hsync_start;
	vbp = mode->vtotal - mode->vsync_end;
	vfp = mode->vsync_start - mode->vdisplay;
	vsw = mode->vsync_end - mode->vsync_start;

	/* INV_PXCK as default (most display sample data on rising edge) */
	if (!(con->display_info.bus_flags & DRM_BUS_FLAG_PIXDATA_POSEDGE))
		pol |= DCU_SYN_POL_INV_PXCK;

	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		pol |= DCU_SYN_POL_INV_HS_LOW;

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		pol |= DCU_SYN_POL_INV_VS_LOW;

	regmap_write(fsl_dev->regmap, DCU_HSYN_PARA,
		     DCU_HSYN_PARA_BP(hbp) |
		     DCU_HSYN_PARA_PW(hsw) |
		     DCU_HSYN_PARA_FP(hfp));
	regmap_write(fsl_dev->regmap, DCU_VSYN_PARA,
		     DCU_VSYN_PARA_BP(vbp) |
		     DCU_VSYN_PARA_PW(vsw) |
		     DCU_VSYN_PARA_FP(vfp));
	regmap_write(fsl_dev->regmap, DCU_DISP_SIZE,
		     DCU_DISP_SIZE_DELTA_Y(mode->vdisplay) |
		     DCU_DISP_SIZE_DELTA_X(mode->hdisplay));
	regmap_write(fsl_dev->regmap, DCU_SYN_POL, pol);
	regmap_write(fsl_dev->regmap, DCU_BGND, DCU_BGND_R(0) |
		     DCU_BGND_G(0) | DCU_BGND_B(0));
	regmap_write(fsl_dev->regmap, DCU_DCU_MODE,
		     DCU_MODE_BLEND_ITER(1) | DCU_MODE_RASTER_EN);
	regmap_write(fsl_dev->regmap, DCU_THRESHOLD,
		     DCU_THRESHOLD_LS_BF_VS(BF_VS_VAL) |
		     DCU_THRESHOLD_OUT_BUF_HIGH(BUF_MAX_VAL) |
		     DCU_THRESHOLD_OUT_BUF_LOW(BUF_MIN_VAL));
	return;
}