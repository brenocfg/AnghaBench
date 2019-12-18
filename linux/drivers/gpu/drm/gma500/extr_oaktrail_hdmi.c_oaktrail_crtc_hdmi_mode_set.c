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
struct oaktrail_hdmi_dev {int dummy; } ;
struct oaktrail_hdmi_clock {int nf; int nr; int np; } ;
struct drm_psb_private {struct oaktrail_hdmi_dev* hdmi_priv; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_display_mode {int crtc_hblank_start; int crtc_hblank_end; int crtc_hsync_start; int crtc_hsync_end; int crtc_vdisplay; int crtc_vtotal; int crtc_vblank_start; int crtc_vblank_end; int crtc_vsync_start; int crtc_vsync_end; int crtc_hdisplay; int crtc_htotal; int vdisplay; int hdisplay; int /*<<< orphan*/  clock; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct drm_crtc_helper_funcs {int /*<<< orphan*/  (* mode_set_base ) (struct drm_crtc*,int,int,struct drm_framebuffer*) ;} ;
struct drm_crtc {struct drm_crtc_helper_funcs* helper_private; struct drm_device* dev; } ;

/* Variables and functions */
 int DISPLAY_PLANE_ENABLE ; 
 int DISPPLANE_GAMMA_ENABLE ; 
 int DISPPLANE_SEL_PIPE_B ; 
 int DPLL_ADJUST ; 
 int DPLL_CLK_ENABLE ; 
 int DPLL_CTRL ; 
 int DPLL_DITHEN ; 
 int DPLL_DIV_CTRL ; 
 int DPLL_ENSTAT ; 
 int DPLL_PDIV_MASK ; 
 int DPLL_PDIV_SHIFT ; 
 int DPLL_PWRDN ; 
 int DPLL_RESET ; 
 int DPLL_STATUS ; 
 int DPLL_UPDATE ; 
 int DSPAPOS ; 
 int DSPASIZE ; 
 int DSPBCNTR ; 
 int DSPBPOS ; 
 int DSPBSIZE ; 
 int HBLANK_A ; 
 int HBLANK_B ; 
 int HDMI_HBLANK_A ; 
 int /*<<< orphan*/  HDMI_WRITE (int,int) ; 
 int HSYNC_A ; 
 int HSYNC_B ; 
 int HTOTAL_A ; 
 int HTOTAL_B ; 
 int PCH_HBLANK_B ; 
 int PCH_HSYNC_B ; 
 int PCH_HTOTAL_B ; 
 int PCH_PIPEBCONF ; 
 int PCH_PIPEBSRC ; 
 int PCH_VBLANK_B ; 
 int PCH_VSYNC_B ; 
 int PCH_VTOTAL_B ; 
 int PIPEACONF ; 
 int PIPEACONF_ENABLE ; 
 int PIPEASRC ; 
 int PIPEBCONF ; 
 int PIPEBSRC ; 
 int REG_READ (int) ; 
 int /*<<< orphan*/  REG_WRITE (int,int) ; 
 int VBLANK_A ; 
 int VBLANK_B ; 
 int VGACNTRL ; 
 int VGA_DISP_DISABLE ; 
 int VSYNC_A ; 
 int VSYNC_B ; 
 int VTOTAL_A ; 
 int VTOTAL_B ; 
 int /*<<< orphan*/  gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int /*<<< orphan*/  gma_wait_for_vblank (struct drm_device*) ; 
 int htotal_calculate (struct drm_display_mode*) ; 
 int /*<<< orphan*/  oaktrail_hdmi_find_dpll (struct drm_crtc*,int /*<<< orphan*/ ,int,struct oaktrail_hdmi_clock*) ; 
 int /*<<< orphan*/  oaktrail_hdmi_reset (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*,int,int,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int oaktrail_crtc_hdmi_mode_set(struct drm_crtc *crtc,
			    struct drm_display_mode *mode,
			    struct drm_display_mode *adjusted_mode,
			    int x, int y,
			    struct drm_framebuffer *old_fb)
{
	struct drm_device *dev = crtc->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	int pipe = 1;
	int htot_reg = (pipe == 0) ? HTOTAL_A : HTOTAL_B;
	int hblank_reg = (pipe == 0) ? HBLANK_A : HBLANK_B;
	int hsync_reg = (pipe == 0) ? HSYNC_A : HSYNC_B;
	int vtot_reg = (pipe == 0) ? VTOTAL_A : VTOTAL_B;
	int vblank_reg = (pipe == 0) ? VBLANK_A : VBLANK_B;
	int vsync_reg = (pipe == 0) ? VSYNC_A : VSYNC_B;
	int dspsize_reg = (pipe == 0) ? DSPASIZE : DSPBSIZE;
	int dsppos_reg = (pipe == 0) ? DSPAPOS : DSPBPOS;
	int pipesrc_reg = (pipe == 0) ? PIPEASRC : PIPEBSRC;
	int pipeconf_reg = (pipe == 0) ? PIPEACONF : PIPEBCONF;
	int refclk;
	struct oaktrail_hdmi_clock clock;
	u32 dspcntr, pipeconf, dpll, temp;
	int dspcntr_reg = DSPBCNTR;

	if (!gma_power_begin(dev, true))
		return 0;

	/* Disable the VGA plane that we never use */
	REG_WRITE(VGACNTRL, VGA_DISP_DISABLE);

	/* Disable dpll if necessary */
	dpll = REG_READ(DPLL_CTRL);
	if ((dpll & DPLL_PWRDN) == 0) {
		REG_WRITE(DPLL_CTRL, dpll | (DPLL_PWRDN | DPLL_RESET));
		REG_WRITE(DPLL_DIV_CTRL, 0x00000000);
		REG_WRITE(DPLL_STATUS, 0x1);
	}
	udelay(150);

	/* Reset controller */
	oaktrail_hdmi_reset(dev);

	/* program and enable dpll */
	refclk = 25000;
	oaktrail_hdmi_find_dpll(crtc, adjusted_mode->clock, refclk, &clock);

	/* Set the DPLL */
	dpll = REG_READ(DPLL_CTRL);
	dpll &= ~DPLL_PDIV_MASK;
	dpll &= ~(DPLL_PWRDN | DPLL_RESET);
	REG_WRITE(DPLL_CTRL, 0x00000008);
	REG_WRITE(DPLL_DIV_CTRL, ((clock.nf << 6) | clock.nr));
	REG_WRITE(DPLL_ADJUST, ((clock.nf >> 14) - 1));
	REG_WRITE(DPLL_CTRL, (dpll | (clock.np << DPLL_PDIV_SHIFT) | DPLL_ENSTAT | DPLL_DITHEN));
	REG_WRITE(DPLL_UPDATE, 0x80000000);
	REG_WRITE(DPLL_CLK_ENABLE, 0x80050102);
	udelay(150);

	/* configure HDMI */
	HDMI_WRITE(0x1004, 0x1fd);
	HDMI_WRITE(0x2000, 0x1);
	HDMI_WRITE(0x2008, 0x0);
	HDMI_WRITE(0x3130, 0x8);
	HDMI_WRITE(0x101c, 0x1800810);

	temp = htotal_calculate(adjusted_mode);
	REG_WRITE(htot_reg, temp);
	REG_WRITE(hblank_reg, (adjusted_mode->crtc_hblank_start - 1) | ((adjusted_mode->crtc_hblank_end - 1) << 16));
	REG_WRITE(hsync_reg, (adjusted_mode->crtc_hsync_start - 1) | ((adjusted_mode->crtc_hsync_end - 1) << 16));
	REG_WRITE(vtot_reg, (adjusted_mode->crtc_vdisplay - 1) | ((adjusted_mode->crtc_vtotal - 1) << 16));
	REG_WRITE(vblank_reg, (adjusted_mode->crtc_vblank_start - 1) | ((adjusted_mode->crtc_vblank_end - 1) << 16));
	REG_WRITE(vsync_reg, (adjusted_mode->crtc_vsync_start - 1) | ((adjusted_mode->crtc_vsync_end - 1) << 16));
	REG_WRITE(pipesrc_reg, ((mode->crtc_hdisplay - 1) << 16) |  (mode->crtc_vdisplay - 1));

	REG_WRITE(PCH_HTOTAL_B, (adjusted_mode->crtc_hdisplay - 1) | ((adjusted_mode->crtc_htotal - 1) << 16));
	REG_WRITE(PCH_HBLANK_B, (adjusted_mode->crtc_hblank_start - 1) | ((adjusted_mode->crtc_hblank_end - 1) << 16));
	REG_WRITE(PCH_HSYNC_B, (adjusted_mode->crtc_hsync_start - 1) | ((adjusted_mode->crtc_hsync_end - 1) << 16));
	REG_WRITE(PCH_VTOTAL_B, (adjusted_mode->crtc_vdisplay - 1) | ((adjusted_mode->crtc_vtotal - 1) << 16));
	REG_WRITE(PCH_VBLANK_B, (adjusted_mode->crtc_vblank_start - 1) | ((adjusted_mode->crtc_vblank_end - 1) << 16));
	REG_WRITE(PCH_VSYNC_B, (adjusted_mode->crtc_vsync_start - 1) | ((adjusted_mode->crtc_vsync_end - 1) << 16));
	REG_WRITE(PCH_PIPEBSRC, ((mode->crtc_hdisplay - 1) << 16) |  (mode->crtc_vdisplay - 1));

	temp = adjusted_mode->crtc_hblank_end - adjusted_mode->crtc_hblank_start;
	HDMI_WRITE(HDMI_HBLANK_A, ((adjusted_mode->crtc_hdisplay - 1) << 16) |  temp);

	REG_WRITE(dspsize_reg, ((mode->vdisplay - 1) << 16) | (mode->hdisplay - 1));
	REG_WRITE(dsppos_reg, 0);

	/* Flush the plane changes */
	{
		const struct drm_crtc_helper_funcs *crtc_funcs = crtc->helper_private;
		crtc_funcs->mode_set_base(crtc, x, y, old_fb);
	}

	/* Set up the display plane register */
	dspcntr = REG_READ(dspcntr_reg);
	dspcntr |= DISPPLANE_GAMMA_ENABLE;
	dspcntr |= DISPPLANE_SEL_PIPE_B;
	dspcntr |= DISPLAY_PLANE_ENABLE;

	/* setup pipeconf */
	pipeconf = REG_READ(pipeconf_reg);
	pipeconf |= PIPEACONF_ENABLE;

	REG_WRITE(pipeconf_reg, pipeconf);
	REG_READ(pipeconf_reg);

	REG_WRITE(PCH_PIPEBCONF, pipeconf);
	REG_READ(PCH_PIPEBCONF);
	gma_wait_for_vblank(dev);

	REG_WRITE(dspcntr_reg, dspcntr);
	gma_wait_for_vblank(dev);

	gma_power_end(dev);

	return 0;
}