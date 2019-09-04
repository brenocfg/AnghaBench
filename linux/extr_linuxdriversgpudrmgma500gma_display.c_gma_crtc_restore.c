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
typedef  scalar_t__ uint32_t ;
struct psb_offset {scalar_t__ palette; scalar_t__ base; scalar_t__ cntr; scalar_t__ conf; scalar_t__ src; scalar_t__ pos; scalar_t__ size; scalar_t__ stride; scalar_t__ vsync; scalar_t__ vblank; scalar_t__ vtotal; scalar_t__ hsync; scalar_t__ hblank; scalar_t__ htotal; scalar_t__ dpll; scalar_t__ fp1; scalar_t__ fp0; } ;
struct psb_intel_crtc_state {int saveDPLL; int saveFP0; int saveFP1; int saveHTOTAL; int saveHBLANK; int saveHSYNC; int saveVTOTAL; int saveVBLANK; int saveVSYNC; int saveDSPSTRIDE; int saveDSPSIZE; int saveDSPPOS; int savePIPESRC; int saveDSPBASE; int savePIPECONF; int saveDSPCNTR; int* savePalette; } ;
struct gma_crtc {size_t pipe; struct psb_intel_crtc_state* crtc_state; } ;
struct drm_psb_private {struct psb_offset* regmap; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int DPLL_VCO_ENABLE ; 
 int /*<<< orphan*/  REG_READ (scalar_t__) ; 
 int /*<<< orphan*/  REG_WRITE (scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gma_wait_for_vblank (struct drm_device*) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void gma_crtc_restore(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct gma_crtc *gma_crtc =  to_gma_crtc(crtc);
	struct psb_intel_crtc_state *crtc_state = gma_crtc->crtc_state;
	const struct psb_offset *map = &dev_priv->regmap[gma_crtc->pipe];
	uint32_t palette_reg;
	int i;

	if (!crtc_state) {
		dev_err(dev->dev, "No crtc state\n");
		return;
	}

	if (crtc_state->saveDPLL & DPLL_VCO_ENABLE) {
		REG_WRITE(map->dpll,
			crtc_state->saveDPLL & ~DPLL_VCO_ENABLE);
		REG_READ(map->dpll);
		udelay(150);
	}

	REG_WRITE(map->fp0, crtc_state->saveFP0);
	REG_READ(map->fp0);

	REG_WRITE(map->fp1, crtc_state->saveFP1);
	REG_READ(map->fp1);

	REG_WRITE(map->dpll, crtc_state->saveDPLL);
	REG_READ(map->dpll);
	udelay(150);

	REG_WRITE(map->htotal, crtc_state->saveHTOTAL);
	REG_WRITE(map->hblank, crtc_state->saveHBLANK);
	REG_WRITE(map->hsync, crtc_state->saveHSYNC);
	REG_WRITE(map->vtotal, crtc_state->saveVTOTAL);
	REG_WRITE(map->vblank, crtc_state->saveVBLANK);
	REG_WRITE(map->vsync, crtc_state->saveVSYNC);
	REG_WRITE(map->stride, crtc_state->saveDSPSTRIDE);

	REG_WRITE(map->size, crtc_state->saveDSPSIZE);
	REG_WRITE(map->pos, crtc_state->saveDSPPOS);

	REG_WRITE(map->src, crtc_state->savePIPESRC);
	REG_WRITE(map->base, crtc_state->saveDSPBASE);
	REG_WRITE(map->conf, crtc_state->savePIPECONF);

	gma_wait_for_vblank(dev);

	REG_WRITE(map->cntr, crtc_state->saveDSPCNTR);
	REG_WRITE(map->base, crtc_state->saveDSPBASE);

	gma_wait_for_vblank(dev);

	palette_reg = map->palette;
	for (i = 0; i < 256; ++i)
		REG_WRITE(palette_reg + (i << 2), crtc_state->savePalette[i]);
}