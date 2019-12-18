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
typedef  int u32 ;
struct psb_offset {int /*<<< orphan*/  dpll; int /*<<< orphan*/  conf; int /*<<< orphan*/  base; int /*<<< orphan*/  cntr; } ;
struct gma_crtc {int pipe; } ;
struct drm_psb_private {struct psb_offset* regmap; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int DISPLAY_PLANE_ENABLE ; 
 int DPLL_VCO_ENABLE ; 
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  DSPARB ; 
 int /*<<< orphan*/  DSPCHICKENBIT ; 
 int /*<<< orphan*/  DSPFW1 ; 
 int /*<<< orphan*/  DSPFW2 ; 
 int /*<<< orphan*/  DSPFW3 ; 
 int /*<<< orphan*/  DSPFW4 ; 
 int /*<<< orphan*/  DSPFW5 ; 
 int /*<<< orphan*/  DSPFW6 ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  INTEL_OUTPUT_SDVO ; 
 int PIPEACONF_ENABLE ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int REG_READ_WITH_AUX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE_WITH_AUX (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  VGACNTRL ; 
 int VGA_DISP_DISABLE ; 
 int /*<<< orphan*/  gma_crtc_load_lut (struct drm_crtc*) ; 
 scalar_t__ gma_pipe_has_type (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int /*<<< orphan*/  gma_wait_for_vblank (struct drm_device*) ; 
 int /*<<< orphan*/  oaktrail_crtc_hdmi_dpms (struct drm_crtc*,int) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void oaktrail_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);
	int pipe = gma_crtc->pipe;
	const struct psb_offset *map = &dev_priv->regmap[pipe];
	u32 temp;
	int i;
	int need_aux = gma_pipe_has_type(crtc, INTEL_OUTPUT_SDVO) ? 1 : 0;

	if (gma_pipe_has_type(crtc, INTEL_OUTPUT_HDMI)) {
		oaktrail_crtc_hdmi_dpms(crtc, mode);
		return;
	}

	if (!gma_power_begin(dev, true))
		return;

	/* XXX: When our outputs are all unaware of DPMS modes other than off
	 * and on, we should map those modes to DRM_MODE_DPMS_OFF in the CRTC.
	 */
	switch (mode) {
	case DRM_MODE_DPMS_ON:
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
		for (i = 0; i <= need_aux; i++) {
			/* Enable the DPLL */
			temp = REG_READ_WITH_AUX(map->dpll, i);
			if ((temp & DPLL_VCO_ENABLE) == 0) {
				REG_WRITE_WITH_AUX(map->dpll, temp, i);
				REG_READ_WITH_AUX(map->dpll, i);
				/* Wait for the clocks to stabilize. */
				udelay(150);
				REG_WRITE_WITH_AUX(map->dpll,
						   temp | DPLL_VCO_ENABLE, i);
				REG_READ_WITH_AUX(map->dpll, i);
				/* Wait for the clocks to stabilize. */
				udelay(150);
				REG_WRITE_WITH_AUX(map->dpll,
						   temp | DPLL_VCO_ENABLE, i);
				REG_READ_WITH_AUX(map->dpll, i);
				/* Wait for the clocks to stabilize. */
				udelay(150);
			}

			/* Enable the pipe */
			temp = REG_READ_WITH_AUX(map->conf, i);
			if ((temp & PIPEACONF_ENABLE) == 0) {
				REG_WRITE_WITH_AUX(map->conf,
						   temp | PIPEACONF_ENABLE, i);
			}

			/* Enable the plane */
			temp = REG_READ_WITH_AUX(map->cntr, i);
			if ((temp & DISPLAY_PLANE_ENABLE) == 0) {
				REG_WRITE_WITH_AUX(map->cntr,
						   temp | DISPLAY_PLANE_ENABLE,
						   i);
				/* Flush the plane changes */
				REG_WRITE_WITH_AUX(map->base,
					REG_READ_WITH_AUX(map->base, i), i);
			}

		}
		gma_crtc_load_lut(crtc);

		/* Give the overlay scaler a chance to enable
		   if it's on this pipe */
		/* psb_intel_crtc_dpms_video(crtc, true); TODO */
		break;
	case DRM_MODE_DPMS_OFF:
		/* Give the overlay scaler a chance to disable
		 * if it's on this pipe */
		/* psb_intel_crtc_dpms_video(crtc, FALSE); TODO */

		for (i = 0; i <= need_aux; i++) {
			/* Disable the VGA plane that we never use */
			REG_WRITE_WITH_AUX(VGACNTRL, VGA_DISP_DISABLE, i);
			/* Disable display plane */
			temp = REG_READ_WITH_AUX(map->cntr, i);
			if ((temp & DISPLAY_PLANE_ENABLE) != 0) {
				REG_WRITE_WITH_AUX(map->cntr,
					temp & ~DISPLAY_PLANE_ENABLE, i);
				/* Flush the plane changes */
				REG_WRITE_WITH_AUX(map->base,
						   REG_READ(map->base), i);
				REG_READ_WITH_AUX(map->base, i);
			}

			/* Next, disable display pipes */
			temp = REG_READ_WITH_AUX(map->conf, i);
			if ((temp & PIPEACONF_ENABLE) != 0) {
				REG_WRITE_WITH_AUX(map->conf,
						   temp & ~PIPEACONF_ENABLE, i);
				REG_READ_WITH_AUX(map->conf, i);
			}
			/* Wait for for the pipe disable to take effect. */
			gma_wait_for_vblank(dev);

			temp = REG_READ_WITH_AUX(map->dpll, i);
			if ((temp & DPLL_VCO_ENABLE) != 0) {
				REG_WRITE_WITH_AUX(map->dpll,
						   temp & ~DPLL_VCO_ENABLE, i);
				REG_READ_WITH_AUX(map->dpll, i);
			}

			/* Wait for the clocks to turn off. */
			udelay(150);
		}
		break;
	}

	/* Set FIFO Watermarks (values taken from EMGD) */
	REG_WRITE(DSPARB, 0x3f80);
	REG_WRITE(DSPFW1, 0x3f8f0404);
	REG_WRITE(DSPFW2, 0x04040f04);
	REG_WRITE(DSPFW3, 0x0);
	REG_WRITE(DSPFW4, 0x04040404);
	REG_WRITE(DSPFW5, 0x04040404);
	REG_WRITE(DSPFW6, 0x78);
	REG_WRITE(DSPCHICKENBIT, REG_READ(DSPCHICKENBIT) | 0xc040);

	gma_power_end(dev);
}