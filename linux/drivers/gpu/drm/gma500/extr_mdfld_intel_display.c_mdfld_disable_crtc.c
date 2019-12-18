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
struct drm_psb_private {struct psb_offset* regmap; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int DISPLAY_PLANE_ENABLE ; 
 int DPLL_VCO_ENABLE ; 
 int HS_CTRL_FIFO_EMPTY ; 
 int HS_DATA_FIFO_EMPTY ; 
 int MDFLD_PWR_GATE_EN ; 
 int /*<<< orphan*/  MIPI_GEN_FIFO_STAT_REG (int) ; 
 int /*<<< orphan*/  PIPEACONF ; 
 int PIPEACONF_ENABLE ; 
 int /*<<< orphan*/  PIPECCONF ; 
 int PIPECONF_CURSOR_OFF ; 
 int PIPECONF_PLANE_OFF ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mdfldWaitForPipeDisable (struct drm_device*,int) ; 
 int /*<<< orphan*/  mdfld_dsi_gen_fifo_ready (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void mdfld_disable_crtc(struct drm_device *dev, int pipe)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	const struct psb_offset *map = &dev_priv->regmap[pipe];
	u32 temp;

	dev_dbg(dev->dev, "pipe = %d\n", pipe);


	if (pipe != 1)
		mdfld_dsi_gen_fifo_ready(dev, MIPI_GEN_FIFO_STAT_REG(pipe),
				HS_CTRL_FIFO_EMPTY | HS_DATA_FIFO_EMPTY);

	/* Disable display plane */
	temp = REG_READ(map->cntr);
	if ((temp & DISPLAY_PLANE_ENABLE) != 0) {
		REG_WRITE(map->cntr,
			  temp & ~DISPLAY_PLANE_ENABLE);
		/* Flush the plane changes */
		REG_WRITE(map->base, REG_READ(map->base));
		REG_READ(map->base);
	}

	/* FIXME_JLIU7 MDFLD_PO revisit */

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
		if ((pipe != 1 &&
			!((REG_READ(PIPEACONF) | REG_READ(PIPECCONF))
				& PIPEACONF_ENABLE)) || pipe == 1) {
			temp &= ~(DPLL_VCO_ENABLE);
			REG_WRITE(map->dpll, temp);
			REG_READ(map->dpll);
			/* Wait for the clocks to turn off. */
			/* FIXME_MDFLD PO may need more delay */
			udelay(500);

			if (!(temp & MDFLD_PWR_GATE_EN)) {
				/* gating power of DPLL */
				REG_WRITE(map->dpll, temp | MDFLD_PWR_GATE_EN);
				/* FIXME_MDFLD PO - change 500 to 1 after PO */
				udelay(5000);
			}
		}
	}

}