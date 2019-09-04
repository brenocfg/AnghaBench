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
struct psb_state {void* saveDSPBCURSOR_POS; void* saveDSPBCURSOR_BASE; void* saveDSPBCURSOR_CTRL; } ;
struct psb_pipe {void** palette; void* tileoff; void* linoff; void* surf; void* addr; void* stride; void* cntr; void* vsync; void* vblank; void* vtotal; void* hsync; void* hblank; void* htotal; void* src; void* conf; } ;
struct oaktrail_hdmi_dev {void* savePCH_VSYNC_B; void* savePCH_VBLANK_B; void* savePCH_VTOTAL_B; void* savePCH_HSYNC_B; void* savePCH_HBLANK_B; void* savePCH_HTOTAL_B; void* savePCH_PIPEBSRC; void* savePCH_PIPEBCONF; void* saveDPLL_CLK_ENABLE; void* saveDPLL_UPDATE; void* saveDPLL_ADJUST; void* saveDPLL_DIV_CTRL; void* saveDPLL_CTRL; } ;
struct TYPE_2__ {struct psb_pipe* pipe; struct psb_state psb; } ;
struct drm_psb_private {TYPE_1__ regs; struct oaktrail_hdmi_dev* hdmi_priv; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ CURBBASE ; 
 scalar_t__ CURBCNTR ; 
 scalar_t__ CURBPOS ; 
 scalar_t__ DPLL_ADJUST ; 
 scalar_t__ DPLL_CLK_ENABLE ; 
 scalar_t__ DPLL_CTRL ; 
 scalar_t__ DPLL_DIV_CTRL ; 
 scalar_t__ DPLL_UPDATE ; 
 scalar_t__ DSPBBASE ; 
 scalar_t__ DSPBCNTR ; 
 scalar_t__ DSPBLINOFF ; 
 scalar_t__ DSPBSTRIDE ; 
 scalar_t__ DSPBSURF ; 
 scalar_t__ DSPBTILEOFF ; 
 scalar_t__ HBLANK_B ; 
 scalar_t__ HSYNC_B ; 
 scalar_t__ HTOTAL_B ; 
 scalar_t__ PALETTE_B ; 
 scalar_t__ PCH_HBLANK_B ; 
 scalar_t__ PCH_HSYNC_B ; 
 scalar_t__ PCH_HTOTAL_B ; 
 scalar_t__ PCH_PIPEBCONF ; 
 scalar_t__ PCH_PIPEBSRC ; 
 scalar_t__ PCH_VBLANK_B ; 
 scalar_t__ PCH_VSYNC_B ; 
 scalar_t__ PCH_VTOTAL_B ; 
 scalar_t__ PIPEBCONF ; 
 scalar_t__ PIPEBSRC ; 
 void* PSB_RVDC32 (scalar_t__) ; 
 scalar_t__ VBLANK_B ; 
 scalar_t__ VSYNC_B ; 
 scalar_t__ VTOTAL_B ; 

void oaktrail_hdmi_save(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	struct psb_state *regs = &dev_priv->regs.psb;
	struct psb_pipe *pipeb = &dev_priv->regs.pipe[1];
	int i;

	/* dpll */
	hdmi_dev->saveDPLL_CTRL = PSB_RVDC32(DPLL_CTRL);
	hdmi_dev->saveDPLL_DIV_CTRL = PSB_RVDC32(DPLL_DIV_CTRL);
	hdmi_dev->saveDPLL_ADJUST = PSB_RVDC32(DPLL_ADJUST);
	hdmi_dev->saveDPLL_UPDATE = PSB_RVDC32(DPLL_UPDATE);
	hdmi_dev->saveDPLL_CLK_ENABLE = PSB_RVDC32(DPLL_CLK_ENABLE);

	/* pipe B */
	pipeb->conf = PSB_RVDC32(PIPEBCONF);
	pipeb->src = PSB_RVDC32(PIPEBSRC);
	pipeb->htotal = PSB_RVDC32(HTOTAL_B);
	pipeb->hblank = PSB_RVDC32(HBLANK_B);
	pipeb->hsync = PSB_RVDC32(HSYNC_B);
	pipeb->vtotal = PSB_RVDC32(VTOTAL_B);
	pipeb->vblank = PSB_RVDC32(VBLANK_B);
	pipeb->vsync = PSB_RVDC32(VSYNC_B);

	hdmi_dev->savePCH_PIPEBCONF = PSB_RVDC32(PCH_PIPEBCONF);
	hdmi_dev->savePCH_PIPEBSRC = PSB_RVDC32(PCH_PIPEBSRC);
	hdmi_dev->savePCH_HTOTAL_B = PSB_RVDC32(PCH_HTOTAL_B);
	hdmi_dev->savePCH_HBLANK_B = PSB_RVDC32(PCH_HBLANK_B);
	hdmi_dev->savePCH_HSYNC_B  = PSB_RVDC32(PCH_HSYNC_B);
	hdmi_dev->savePCH_VTOTAL_B = PSB_RVDC32(PCH_VTOTAL_B);
	hdmi_dev->savePCH_VBLANK_B = PSB_RVDC32(PCH_VBLANK_B);
	hdmi_dev->savePCH_VSYNC_B  = PSB_RVDC32(PCH_VSYNC_B);

	/* plane */
	pipeb->cntr = PSB_RVDC32(DSPBCNTR);
	pipeb->stride = PSB_RVDC32(DSPBSTRIDE);
	pipeb->addr = PSB_RVDC32(DSPBBASE);
	pipeb->surf = PSB_RVDC32(DSPBSURF);
	pipeb->linoff = PSB_RVDC32(DSPBLINOFF);
	pipeb->tileoff = PSB_RVDC32(DSPBTILEOFF);

	/* cursor B */
	regs->saveDSPBCURSOR_CTRL = PSB_RVDC32(CURBCNTR);
	regs->saveDSPBCURSOR_BASE = PSB_RVDC32(CURBBASE);
	regs->saveDSPBCURSOR_POS = PSB_RVDC32(CURBPOS);

	/* save palette */
	for (i = 0; i < 256; i++)
		pipeb->palette[i] = PSB_RVDC32(PALETTE_B + (i << 2));
}