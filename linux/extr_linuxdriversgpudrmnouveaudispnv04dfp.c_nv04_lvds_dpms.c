#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  clock; } ;
struct nouveau_encoder {int last_dpms; TYPE_5__* dcb; TYPE_2__ mode; } ;
struct nouveau_drm {int dummy; } ;
struct drm_encoder {struct drm_crtc* crtc; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_13__ {int index; } ;
struct TYPE_8__ {scalar_t__ use_power_scripts; } ;
struct TYPE_12__ {TYPE_1__ lvdsconf; int /*<<< orphan*/  index; } ;
struct TYPE_10__ {int sel_clk; } ;
struct TYPE_11__ {TYPE_3__ mode_reg; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  LVDS_PANEL_OFF ; 
 int /*<<< orphan*/  LVDS_PANEL_ON ; 
 int NVReadRAMDAC (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_PRAMDAC_SEL_CLK ; 
 int /*<<< orphan*/  call_lvds_script (struct drm_device*,TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_powersaving_dpms (int) ; 
 TYPE_6__* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_encoder* nouveau_encoder (struct drm_encoder*) ; 
 int nv04_dfp_get_bound_head (struct drm_device*,TYPE_5__*) ; 
 int /*<<< orphan*/  nv04_dfp_prepare_sel_clk (struct drm_device*,struct nouveau_encoder*,int) ; 
 int /*<<< orphan*/  nv04_dfp_update_backlight (struct drm_encoder*,int) ; 
 int /*<<< orphan*/  nv04_dfp_update_fp_control (struct drm_encoder*,int) ; 
 TYPE_4__* nv04_display (struct drm_device*) ; 

__attribute__((used)) static void nv04_lvds_dpms(struct drm_encoder *encoder, int mode)
{
	struct drm_device *dev = encoder->dev;
	struct drm_crtc *crtc = encoder->crtc;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	bool was_powersaving = is_powersaving_dpms(nv_encoder->last_dpms);

	if (nv_encoder->last_dpms == mode)
		return;
	nv_encoder->last_dpms = mode;

	NV_DEBUG(drm, "Setting dpms mode %d on lvds encoder (output %d)\n",
		 mode, nv_encoder->dcb->index);

	if (was_powersaving && is_powersaving_dpms(mode))
		return;

	if (nv_encoder->dcb->lvdsconf.use_power_scripts) {
		/* when removing an output, crtc may not be set, but PANEL_OFF
		 * must still be run
		 */
		int head = crtc ? nouveau_crtc(crtc)->index :
			   nv04_dfp_get_bound_head(dev, nv_encoder->dcb);

		if (mode == DRM_MODE_DPMS_ON) {
			call_lvds_script(dev, nv_encoder->dcb, head,
					 LVDS_PANEL_ON, nv_encoder->mode.clock);
		} else
			/* pxclk of 0 is fine for PANEL_OFF, and for a
			 * disconnected LVDS encoder there is no native_mode
			 */
			call_lvds_script(dev, nv_encoder->dcb, head,
					 LVDS_PANEL_OFF, 0);
	}

	nv04_dfp_update_backlight(encoder, mode);
	nv04_dfp_update_fp_control(encoder, mode);

	if (mode == DRM_MODE_DPMS_ON)
		nv04_dfp_prepare_sel_clk(dev, nv_encoder, nouveau_crtc(crtc)->index);
	else {
		nv04_display(dev)->mode_reg.sel_clk = NVReadRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK);
		nv04_display(dev)->mode_reg.sel_clk &= ~0xf0;
	}
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_SEL_CLK, nv04_display(dev)->mode_reg.sel_clk);
}