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
struct psb_offset {int dpll; int conf; int cntr; int base; int status; } ;
struct gma_crtc {int pipe; } ;
struct drm_psb_private {int* pipeconf; struct psb_offset* regmap; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int DISPLAY_PLANE_ENABLE ; 
 int DPLL_VCO_ENABLE ; 
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int HS_CTRL_FIFO_EMPTY ; 
 int HS_DATA_FIFO_EMPTY ; 
 int MDFLD_PWR_GATE_EN ; 
 int MIPI_DEVICE_READY_REG (int) ; 
 int /*<<< orphan*/  MIPI_GEN_FIFO_STAT_REG (int) ; 
 int PIPEACONF ; 
 int PIPEACONF_ENABLE ; 
 int PIPECCONF ; 
 int PIPECONF_CURSOR_OFF ; 
 int PIPECONF_DSIPLL_LOCK ; 
 int PIPECONF_PLANE_OFF ; 
 int PIPE_VBLANK_STATUS ; 
 int REG_READ (int) ; 
 int /*<<< orphan*/  REG_WRITE (int,int) ; 
 int VGACNTRL ; 
 int VGA_DISP_DISABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gma_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int /*<<< orphan*/  mdfldWaitForPipeDisable (struct drm_device*,int) ; 
 int /*<<< orphan*/  mdfldWaitForPipeEnable (struct drm_device*,int) ; 
 int /*<<< orphan*/  mdfld_dsi_gen_fifo_ready (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mdfld_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);
	int pipe = gma_crtc->pipe;
	const struct psb_offset *map = &dev_priv->regmap[pipe];
	u32 pipeconf = dev_priv->pipeconf[pipe];
	u32 temp;
	int timeout = 0;

	dev_dbg(dev->dev, "mode = %d, pipe = %d\n", mode, pipe);

	/* Note: Old code uses pipe a stat for pipe b but that appears
	   to be a bug */

	if (!gma_power_begin(dev, true))
		return;

	/* XXX: When our outputs are all unaware of DPMS modes other than off
	 * and on, we should map those modes to DRM_MODE_DPMS_OFF in the CRTC.
	 */
	switch (mode) {
	case DRM_MODE_DPMS_ON:
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
		/* Enable the DPLL */
		temp = REG_READ(map->dpll);

		if ((temp & DPLL_VCO_ENABLE) == 0) {
			/* When ungating power of DPLL, needs to wait 0.5us
			   before enable the VCO */
			if (temp & MDFLD_PWR_GATE_EN) {
				temp &= ~MDFLD_PWR_GATE_EN;
				REG_WRITE(map->dpll, temp);
				/* FIXME_MDFLD PO - change 500 to 1 after PO */
				udelay(500);
			}

			REG_WRITE(map->dpll, temp);
			REG_READ(map->dpll);
			/* FIXME_MDFLD PO - change 500 to 1 after PO */
			udelay(500);

			REG_WRITE(map->dpll, temp | DPLL_VCO_ENABLE);
			REG_READ(map->dpll);

			/**
			 * wait for DSI PLL to lock
			 * NOTE: only need to poll status of pipe 0 and pipe 1,
			 * since both MIPI pipes share the same PLL.
			 */
			while ((pipe != 2) && (timeout < 20000) &&
			  !(REG_READ(map->conf) & PIPECONF_DSIPLL_LOCK)) {
				udelay(150);
				timeout++;
			}
		}

		/* Enable the plane */
		temp = REG_READ(map->cntr);
		if ((temp & DISPLAY_PLANE_ENABLE) == 0) {
			REG_WRITE(map->cntr,
				temp | DISPLAY_PLANE_ENABLE);
			/* Flush the plane changes */
			REG_WRITE(map->base, REG_READ(map->base));
		}

		/* Enable the pipe */
		temp = REG_READ(map->conf);
		if ((temp & PIPEACONF_ENABLE) == 0) {
			REG_WRITE(map->conf, pipeconf);

			/* Wait for for the pipe enable to take effect. */
			mdfldWaitForPipeEnable(dev, pipe);
		}

		/*workaround for sighting 3741701 Random X blank display*/
		/*perform w/a in video mode only on pipe A or C*/
		if (pipe == 0 || pipe == 2) {
			REG_WRITE(map->status, REG_READ(map->status));
			msleep(100);
			if (PIPE_VBLANK_STATUS & REG_READ(map->status))
				dev_dbg(dev->dev, "OK");
			else {
				dev_dbg(dev->dev, "STUCK!!!!");
				/*shutdown controller*/
				temp = REG_READ(map->cntr);
				REG_WRITE(map->cntr,
						temp & ~DISPLAY_PLANE_ENABLE);
				REG_WRITE(map->base, REG_READ(map->base));
				/*mdfld_dsi_dpi_shut_down(dev, pipe);*/
				REG_WRITE(0xb048, 1);
				msleep(100);
				temp = REG_READ(map->conf);
				temp &= ~PIPEACONF_ENABLE;
				REG_WRITE(map->conf, temp);
				msleep(100); /*wait for pipe disable*/
				REG_WRITE(MIPI_DEVICE_READY_REG(pipe), 0);
				msleep(100);
				REG_WRITE(0xb004, REG_READ(0xb004));
				/* try to bring the controller back up again*/
				REG_WRITE(MIPI_DEVICE_READY_REG(pipe), 1);
				temp = REG_READ(map->cntr);
				REG_WRITE(map->cntr,
						temp | DISPLAY_PLANE_ENABLE);
				REG_WRITE(map->base, REG_READ(map->base));
				/*mdfld_dsi_dpi_turn_on(dev, pipe);*/
				REG_WRITE(0xb048, 2);
				msleep(100);
				temp = REG_READ(map->conf);
				temp |= PIPEACONF_ENABLE;
				REG_WRITE(map->conf, temp);
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
		if (pipe != 1)
			mdfld_dsi_gen_fifo_ready(dev,
				MIPI_GEN_FIFO_STAT_REG(pipe),
				HS_CTRL_FIFO_EMPTY | HS_DATA_FIFO_EMPTY);

		/* Disable the VGA plane that we never use */
		REG_WRITE(VGACNTRL, VGA_DISP_DISABLE);

		/* Disable display plane */
		temp = REG_READ(map->cntr);
		if ((temp & DISPLAY_PLANE_ENABLE) != 0) {
			REG_WRITE(map->cntr,
				  temp & ~DISPLAY_PLANE_ENABLE);
			/* Flush the plane changes */
			REG_WRITE(map->base, REG_READ(map->base));
			REG_READ(map->base);
		}

		/* Next, disable display pipes */
		temp = REG_READ(map->conf);
		if ((temp & PIPEACONF_ENABLE) != 0) {
			temp &= ~PIPEACONF_ENABLE;
			temp |= PIPECONF_PLANE_OFF | PIPECONF_CURSOR_OFF;
			REG_WRITE(map->conf, temp);
			REG_READ(map->conf);

			/* Wait for for the pipe disable to take effect. */
			mdfldWaitForPipeDisable(dev, pipe);
		}

		temp = REG_READ(map->dpll);
		if (temp & DPLL_VCO_ENABLE) {
			if ((pipe != 1 && !((REG_READ(PIPEACONF)
				| REG_READ(PIPECCONF)) & PIPEACONF_ENABLE))
					|| pipe == 1) {
				temp &= ~(DPLL_VCO_ENABLE);
				REG_WRITE(map->dpll, temp);
				REG_READ(map->dpll);
				/* Wait for the clocks to turn off. */
				/* FIXME_MDFLD PO may need more delay */
				udelay(500);
			}
		}
		break;
	}
	gma_power_end(dev);
}