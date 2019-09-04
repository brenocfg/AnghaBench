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
typedef  int u16 ;
struct ivch_priv {int* reg_backup; } ;
struct intel_dvo_device {struct ivch_priv* dev_priv; } ;
struct drm_display_mode {int hdisplay; int crtc_hdisplay; int vdisplay; int crtc_vdisplay; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR01 ; 
 int VR01_DITHER_ENABLE ; 
 int VR01_PANEL_FIT_ENABLE ; 
 int VR10_INTERFACE_1X18 ; 
 int VR10_INTERFACE_2X18 ; 
 int VR10_INTERFACE_DEPTH_MASK ; 
 int /*<<< orphan*/  VR40 ; 
 int VR40_AUTO_RATIO_ENABLE ; 
 int VR40_CLOCK_GATING_ENABLE ; 
 int VR40_HORIZONTAL_INTERP_ENABLE ; 
 int VR40_STALL_ENABLE ; 
 int VR40_VERTICAL_INTERP_ENABLE ; 
 int /*<<< orphan*/  VR41 ; 
 int /*<<< orphan*/  VR42 ; 
 int /*<<< orphan*/  backup_addresses ; 
 int /*<<< orphan*/  ivch_reset (struct intel_dvo_device*) ; 
 int /*<<< orphan*/  ivch_write (struct intel_dvo_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ivch_mode_set(struct intel_dvo_device *dvo,
			  const struct drm_display_mode *mode,
			  const struct drm_display_mode *adjusted_mode)
{
	struct ivch_priv *priv = dvo->dev_priv;
	u16 vr40 = 0;
	u16 vr01 = 0;
	u16 vr10;

	ivch_reset(dvo);

	vr10 = priv->reg_backup[ARRAY_SIZE(backup_addresses) - 1];

	/* Enable dithering for 18 bpp pipelines */
	vr10 &= VR10_INTERFACE_DEPTH_MASK;
	if (vr10 == VR10_INTERFACE_2X18 || vr10 == VR10_INTERFACE_1X18)
		vr01 = VR01_DITHER_ENABLE;

	vr40 = (VR40_STALL_ENABLE | VR40_VERTICAL_INTERP_ENABLE |
		VR40_HORIZONTAL_INTERP_ENABLE);

	if (mode->hdisplay != adjusted_mode->crtc_hdisplay ||
	    mode->vdisplay != adjusted_mode->crtc_vdisplay) {
		u16 x_ratio, y_ratio;

		vr01 |= VR01_PANEL_FIT_ENABLE;
		vr40 |= VR40_CLOCK_GATING_ENABLE;
		x_ratio = (((mode->hdisplay - 1) << 16) /
			   (adjusted_mode->crtc_hdisplay - 1)) >> 2;
		y_ratio = (((mode->vdisplay - 1) << 16) /
			   (adjusted_mode->crtc_vdisplay - 1)) >> 2;
		ivch_write(dvo, VR42, x_ratio);
		ivch_write(dvo, VR41, y_ratio);
	} else {
		vr01 &= ~VR01_PANEL_FIT_ENABLE;
		vr40 &= ~VR40_CLOCK_GATING_ENABLE;
	}
	vr40 &= ~VR40_AUTO_RATIO_ENABLE;

	ivch_write(dvo, VR01, vr01);
	ivch_write(dvo, VR40, vr40);
}