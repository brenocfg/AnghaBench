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
struct videomode {int flags; int /*<<< orphan*/  hactive; int /*<<< orphan*/  vactive; int /*<<< orphan*/  vfront_porch; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  vback_porch; int /*<<< orphan*/  hfront_porch; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  hback_porch; } ;
struct TYPE_6__ {int bus_flags; } ;
struct drm_connector {TYPE_3__ display_info; } ;
struct TYPE_4__ {struct drm_connector base; } ;
struct fsl_dcu_drm_device {int /*<<< orphan*/  regmap; int /*<<< orphan*/  pix_clk; TYPE_1__ connector; } ;
struct drm_display_mode {int clock; } ;
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
 unsigned int DCU_DISP_SIZE_DELTA_X (int /*<<< orphan*/ ) ; 
 unsigned int DCU_DISP_SIZE_DELTA_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCU_HSYN_PARA ; 
 unsigned int DCU_HSYN_PARA_BP (int /*<<< orphan*/ ) ; 
 unsigned int DCU_HSYN_PARA_FP (int /*<<< orphan*/ ) ; 
 unsigned int DCU_HSYN_PARA_PW (int /*<<< orphan*/ ) ; 
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
 unsigned int DCU_VSYN_PARA_BP (int /*<<< orphan*/ ) ; 
 unsigned int DCU_VSYN_PARA_FP (int /*<<< orphan*/ ) ; 
 unsigned int DCU_VSYN_PARA_PW (int /*<<< orphan*/ ) ; 
 int DISPLAY_FLAGS_HSYNC_LOW ; 
 int DISPLAY_FLAGS_VSYNC_LOW ; 
 int DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_display_mode_to_videomode (struct drm_display_mode*,struct videomode*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void fsl_dcu_drm_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct fsl_dcu_drm_device *fsl_dev = dev->dev_private;
	struct drm_connector *con = &fsl_dev->connector.base;
	struct drm_display_mode *mode = &crtc->state->mode;
	unsigned int pol = 0;
	struct videomode vm;

	clk_set_rate(fsl_dev->pix_clk, mode->clock * 1000);

	drm_display_mode_to_videomode(mode, &vm);

	/* INV_PXCK as default (most display sample data on rising edge) */
	if (!(con->display_info.bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE))
		pol |= DCU_SYN_POL_INV_PXCK;

	if (vm.flags & DISPLAY_FLAGS_HSYNC_LOW)
		pol |= DCU_SYN_POL_INV_HS_LOW;

	if (vm.flags & DISPLAY_FLAGS_VSYNC_LOW)
		pol |= DCU_SYN_POL_INV_VS_LOW;

	regmap_write(fsl_dev->regmap, DCU_HSYN_PARA,
		     DCU_HSYN_PARA_BP(vm.hback_porch) |
		     DCU_HSYN_PARA_PW(vm.hsync_len) |
		     DCU_HSYN_PARA_FP(vm.hfront_porch));
	regmap_write(fsl_dev->regmap, DCU_VSYN_PARA,
		     DCU_VSYN_PARA_BP(vm.vback_porch) |
		     DCU_VSYN_PARA_PW(vm.vsync_len) |
		     DCU_VSYN_PARA_FP(vm.vfront_porch));
	regmap_write(fsl_dev->regmap, DCU_DISP_SIZE,
		     DCU_DISP_SIZE_DELTA_Y(vm.vactive) |
		     DCU_DISP_SIZE_DELTA_X(vm.hactive));
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