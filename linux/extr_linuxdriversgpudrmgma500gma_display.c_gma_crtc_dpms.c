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
typedef  int u32 ;
struct psb_offset {int /*<<< orphan*/  dpll; int /*<<< orphan*/  conf; int /*<<< orphan*/  base; int /*<<< orphan*/  cntr; int /*<<< orphan*/  status; } ;
struct gma_crtc {int pipe; int active; } ;
struct drm_psb_private {TYPE_1__* ops; struct psb_offset* regmap; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_wm ) (struct drm_device*,struct drm_crtc*) ;int /*<<< orphan*/  (* disable_sr ) (struct drm_device*) ;} ;

/* Variables and functions */
 int DISPLAY_PLANE_ENABLE ; 
 int DPLL_VCO_ENABLE ; 
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  DSPARB ; 
 scalar_t__ IS_CDV (struct drm_device*) ; 
 int PIPEACONF_ENABLE ; 
 int PIPE_FIFO_UNDERRUN ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VGACNTRL ; 
 int VGA_DISP_DISABLE ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  gma_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  gma_wait_for_vblank (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*,struct drm_crtc*) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void gma_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);
	int pipe = gma_crtc->pipe;
	const struct psb_offset *map = &dev_priv->regmap[pipe];
	u32 temp;

	/* XXX: When our outputs are all unaware of DPMS modes other than off
	 * and on, we should map those modes to DRM_MODE_DPMS_OFF in the CRTC.
	 */

	if (IS_CDV(dev))
		dev_priv->ops->disable_sr(dev);

	switch (mode) {
	case DRM_MODE_DPMS_ON:
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
		if (gma_crtc->active)
			break;

		gma_crtc->active = true;

		/* Enable the DPLL */
		temp = REG_READ(map->dpll);
		if ((temp & DPLL_VCO_ENABLE) == 0) {
			REG_WRITE(map->dpll, temp);
			REG_READ(map->dpll);
			/* Wait for the clocks to stabilize. */
			udelay(150);
			REG_WRITE(map->dpll, temp | DPLL_VCO_ENABLE);
			REG_READ(map->dpll);
			/* Wait for the clocks to stabilize. */
			udelay(150);
			REG_WRITE(map->dpll, temp | DPLL_VCO_ENABLE);
			REG_READ(map->dpll);
			/* Wait for the clocks to stabilize. */
			udelay(150);
		}

		/* Enable the plane */
		temp = REG_READ(map->cntr);
		if ((temp & DISPLAY_PLANE_ENABLE) == 0) {
			REG_WRITE(map->cntr,
				  temp | DISPLAY_PLANE_ENABLE);
			/* Flush the plane changes */
			REG_WRITE(map->base, REG_READ(map->base));
		}

		udelay(150);

		/* Enable the pipe */
		temp = REG_READ(map->conf);
		if ((temp & PIPEACONF_ENABLE) == 0)
			REG_WRITE(map->conf, temp | PIPEACONF_ENABLE);

		temp = REG_READ(map->status);
		temp &= ~(0xFFFF);
		temp |= PIPE_FIFO_UNDERRUN;
		REG_WRITE(map->status, temp);
		REG_READ(map->status);

		gma_crtc_load_lut(crtc);

		/* Give the overlay scaler a chance to enable
		 * if it's on this pipe */
		/* psb_intel_crtc_dpms_video(crtc, true); TODO */
		break;
	case DRM_MODE_DPMS_OFF:
		if (!gma_crtc->active)
			break;

		gma_crtc->active = false;

		/* Give the overlay scaler a chance to disable
		 * if it's on this pipe */
		/* psb_intel_crtc_dpms_video(crtc, FALSE); TODO */

		/* Disable the VGA plane that we never use */
		REG_WRITE(VGACNTRL, VGA_DISP_DISABLE);

		/* Turn off vblank interrupts */
		drm_crtc_vblank_off(crtc);

		/* Wait for vblank for the disable to take effect */
		gma_wait_for_vblank(dev);

		/* Disable plane */
		temp = REG_READ(map->cntr);
		if ((temp & DISPLAY_PLANE_ENABLE) != 0) {
			REG_WRITE(map->cntr,
				  temp & ~DISPLAY_PLANE_ENABLE);
			/* Flush the plane changes */
			REG_WRITE(map->base, REG_READ(map->base));
			REG_READ(map->base);
		}

		/* Disable pipe */
		temp = REG_READ(map->conf);
		if ((temp & PIPEACONF_ENABLE) != 0) {
			REG_WRITE(map->conf, temp & ~PIPEACONF_ENABLE);
			REG_READ(map->conf);
		}

		/* Wait for vblank for the disable to take effect. */
		gma_wait_for_vblank(dev);

		udelay(150);

		/* Disable DPLL */
		temp = REG_READ(map->dpll);
		if ((temp & DPLL_VCO_ENABLE) != 0) {
			REG_WRITE(map->dpll, temp & ~DPLL_VCO_ENABLE);
			REG_READ(map->dpll);
		}

		/* Wait for the clocks to turn off. */
		udelay(150);
		break;
	}

	if (IS_CDV(dev))
		dev_priv->ops->update_wm(dev, crtc);

	/* Set FIFO watermarks */
	REG_WRITE(DSPARB, 0x3F3E);
}