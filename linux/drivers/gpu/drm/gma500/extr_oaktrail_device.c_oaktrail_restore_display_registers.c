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
struct TYPE_2__ {int saveDSPARB; int saveDSPFW1; int saveDSPFW2; int saveDSPFW3; int saveDSPFW4; int saveDSPFW5; int saveDSPFW6; int saveCHICKENBIT; int saveBCLRPAT_A; int savePERF_MODE; int saveDSPACURSOR_CTRL; int saveDSPACURSOR_POS; int saveDSPACURSOR_BASE; int saveLVDS; int savePFIT_CONTROL; int savePFIT_PGM_RATIOS; int savePFIT_AUTO_RATIOS; int savePP_ON_DELAYS; int savePP_OFF_DELAYS; int savePP_DIVISOR; int savePP_CONTROL; int saveOV_OVADD; int saveOV_OGAMC0; int saveOV_OGAMC1; int saveOV_OGAMC2; int saveOV_OGAMC3; int saveOV_OGAMC4; int saveOV_OGAMC5; int saveHISTOGRAM_INT_CONTROL_REG; int saveHISTOGRAM_LOGIC_CONTROL_REG; int savePWM_CONTROL_LOGIC; } ;
struct psb_save_area {int saveBLC_PWM_CTL2; int saveBLC_PWM_CTL; TYPE_1__ psb; struct psb_pipe* pipe; } ;
struct psb_pipe {int fp0; int fp1; int dpll; int htotal; int hblank; int hsync; int vtotal; int vblank; int vsync; int src; int conf; int linoff; int stride; int tileoff; int cntr; int surf; int* palette; } ;
struct drm_psb_private {scalar_t__ iLVDS_enable; scalar_t__ hdmi_priv; struct psb_save_area regs; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ BCLRPAT_A ; 
 scalar_t__ BLC_PWM_CTL ; 
 scalar_t__ BLC_PWM_CTL2 ; 
 scalar_t__ CURABASE ; 
 scalar_t__ CURACNTR ; 
 scalar_t__ CURAPOS ; 
 scalar_t__ DSPACNTR ; 
 scalar_t__ DSPALINOFF ; 
 scalar_t__ DSPARB ; 
 scalar_t__ DSPASTRIDE ; 
 scalar_t__ DSPASURF ; 
 scalar_t__ DSPATILEOFF ; 
 scalar_t__ DSPCHICKENBIT ; 
 scalar_t__ DSPFW1 ; 
 scalar_t__ DSPFW2 ; 
 scalar_t__ DSPFW3 ; 
 scalar_t__ DSPFW4 ; 
 scalar_t__ DSPFW5 ; 
 scalar_t__ DSPFW6 ; 
 scalar_t__ HBLANK_A ; 
 scalar_t__ HISTOGRAM_INT_CONTROL ; 
 scalar_t__ HISTOGRAM_LOGIC_CONTROL ; 
 scalar_t__ HSYNC_A ; 
 scalar_t__ HTOTAL_A ; 
 scalar_t__ LVDS ; 
 scalar_t__ LVDSPP_OFF ; 
 scalar_t__ LVDSPP_ON ; 
 scalar_t__ MRST_DPLL_A ; 
 scalar_t__ MRST_FPA0 ; 
 scalar_t__ MRST_FPA1 ; 
 scalar_t__ MRST_PERF_MODE ; 
 scalar_t__ OV_OGAMC0 ; 
 scalar_t__ OV_OGAMC1 ; 
 scalar_t__ OV_OGAMC2 ; 
 scalar_t__ OV_OGAMC3 ; 
 scalar_t__ OV_OGAMC4 ; 
 scalar_t__ OV_OGAMC5 ; 
 scalar_t__ OV_OVADD ; 
 scalar_t__ PALETTE_A ; 
 scalar_t__ PFIT_AUTO_RATIOS ; 
 scalar_t__ PFIT_CONTROL ; 
 scalar_t__ PFIT_PGM_RATIOS ; 
 scalar_t__ PIPEACONF ; 
 scalar_t__ PIPEASRC ; 
 scalar_t__ PP_CONTROL ; 
 scalar_t__ PP_CYCLE ; 
 int /*<<< orphan*/  PP_STATUS ; 
 int PSB_RVDC32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSB_WVDC32 (int,scalar_t__) ; 
 scalar_t__ PWM_CONTROL_LOGIC ; 
 scalar_t__ VBLANK_A ; 
 scalar_t__ VGACNTRL ; 
 scalar_t__ VSYNC_A ; 
 scalar_t__ VTOTAL_A ; 
 int /*<<< orphan*/  oaktrail_hdmi_restore (struct drm_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int oaktrail_restore_display_registers(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct psb_save_area *regs = &dev_priv->regs;
	struct psb_pipe *p = &regs->pipe[0];
	u32 pp_stat;
	int i;

	/* Display arbitration + watermarks */
	PSB_WVDC32(regs->psb.saveDSPARB, DSPARB);
	PSB_WVDC32(regs->psb.saveDSPFW1, DSPFW1);
	PSB_WVDC32(regs->psb.saveDSPFW2, DSPFW2);
	PSB_WVDC32(regs->psb.saveDSPFW3, DSPFW3);
	PSB_WVDC32(regs->psb.saveDSPFW4, DSPFW4);
	PSB_WVDC32(regs->psb.saveDSPFW5, DSPFW5);
	PSB_WVDC32(regs->psb.saveDSPFW6, DSPFW6);
	PSB_WVDC32(regs->psb.saveCHICKENBIT, DSPCHICKENBIT);

	/* Make sure VGA plane is off. it initializes to on after reset!*/
	PSB_WVDC32(0x80000000, VGACNTRL);

	/* set the plls */
	PSB_WVDC32(p->fp0, MRST_FPA0);
	PSB_WVDC32(p->fp1, MRST_FPA1);

	/* Actually enable it */
	PSB_WVDC32(p->dpll, MRST_DPLL_A);
	udelay(150);

	/* Restore mode */
	PSB_WVDC32(p->htotal, HTOTAL_A);
	PSB_WVDC32(p->hblank, HBLANK_A);
	PSB_WVDC32(p->hsync, HSYNC_A);
	PSB_WVDC32(p->vtotal, VTOTAL_A);
	PSB_WVDC32(p->vblank, VBLANK_A);
	PSB_WVDC32(p->vsync, VSYNC_A);
	PSB_WVDC32(p->src, PIPEASRC);
	PSB_WVDC32(regs->psb.saveBCLRPAT_A, BCLRPAT_A);

	/* Restore performance mode*/
	PSB_WVDC32(regs->psb.savePERF_MODE, MRST_PERF_MODE);

	/* Enable the pipe*/
	if (dev_priv->iLVDS_enable)
		PSB_WVDC32(p->conf, PIPEACONF);

	/* Set up the plane*/
	PSB_WVDC32(p->linoff, DSPALINOFF);
	PSB_WVDC32(p->stride, DSPASTRIDE);
	PSB_WVDC32(p->tileoff, DSPATILEOFF);

	/* Enable the plane */
	PSB_WVDC32(p->cntr, DSPACNTR);
	PSB_WVDC32(p->surf, DSPASURF);

	/* Enable Cursor A */
	PSB_WVDC32(regs->psb.saveDSPACURSOR_CTRL, CURACNTR);
	PSB_WVDC32(regs->psb.saveDSPACURSOR_POS, CURAPOS);
	PSB_WVDC32(regs->psb.saveDSPACURSOR_BASE, CURABASE);

	/* Restore palette (gamma) */
	for (i = 0; i < 256; i++)
		PSB_WVDC32(p->palette[i], PALETTE_A + (i << 2));

	if (dev_priv->hdmi_priv)
		oaktrail_hdmi_restore(dev);

	if (dev_priv->iLVDS_enable) {
		PSB_WVDC32(regs->saveBLC_PWM_CTL2, BLC_PWM_CTL2);
		PSB_WVDC32(regs->psb.saveLVDS, LVDS); /*port 61180h*/
		PSB_WVDC32(regs->psb.savePFIT_CONTROL, PFIT_CONTROL);
		PSB_WVDC32(regs->psb.savePFIT_PGM_RATIOS, PFIT_PGM_RATIOS);
		PSB_WVDC32(regs->psb.savePFIT_AUTO_RATIOS, PFIT_AUTO_RATIOS);
		PSB_WVDC32(regs->saveBLC_PWM_CTL, BLC_PWM_CTL);
		PSB_WVDC32(regs->psb.savePP_ON_DELAYS, LVDSPP_ON);
		PSB_WVDC32(regs->psb.savePP_OFF_DELAYS, LVDSPP_OFF);
		PSB_WVDC32(regs->psb.savePP_DIVISOR, PP_CYCLE);
		PSB_WVDC32(regs->psb.savePP_CONTROL, PP_CONTROL);
	}

	/* Wait for cycle delay */
	do {
		pp_stat = PSB_RVDC32(PP_STATUS);
	} while (pp_stat & 0x08000000);

	/* Wait for panel power up */
	do {
		pp_stat = PSB_RVDC32(PP_STATUS);
	} while (pp_stat & 0x10000000);

	/* Restore HW overlay */
	PSB_WVDC32(regs->psb.saveOV_OVADD, OV_OVADD);
	PSB_WVDC32(regs->psb.saveOV_OGAMC0, OV_OGAMC0);
	PSB_WVDC32(regs->psb.saveOV_OGAMC1, OV_OGAMC1);
	PSB_WVDC32(regs->psb.saveOV_OGAMC2, OV_OGAMC2);
	PSB_WVDC32(regs->psb.saveOV_OGAMC3, OV_OGAMC3);
	PSB_WVDC32(regs->psb.saveOV_OGAMC4, OV_OGAMC4);
	PSB_WVDC32(regs->psb.saveOV_OGAMC5, OV_OGAMC5);

	/* DPST registers */
	PSB_WVDC32(regs->psb.saveHISTOGRAM_INT_CONTROL_REG,
						HISTOGRAM_INT_CONTROL);
	PSB_WVDC32(regs->psb.saveHISTOGRAM_LOGIC_CONTROL_REG,
						HISTOGRAM_LOGIC_CONTROL);
	PSB_WVDC32(regs->psb.savePWM_CONTROL_LOGIC, PWM_CONTROL_LOGIC);

	return 0;
}