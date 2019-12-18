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
struct psb_offset {scalar_t__ palette; scalar_t__ base; scalar_t__ pos; scalar_t__ size; scalar_t__ stride; scalar_t__ vsync; scalar_t__ vblank; scalar_t__ vtotal; scalar_t__ hsync; scalar_t__ hblank; scalar_t__ htotal; scalar_t__ dpll; scalar_t__ fp1; scalar_t__ fp0; scalar_t__ src; scalar_t__ conf; scalar_t__ cntr; } ;
struct psb_intel_crtc_state {void** savePalette; void* saveDSPBASE; void* saveDSPPOS; void* saveDSPSIZE; void* saveDSPSTRIDE; void* saveVSYNC; void* saveVBLANK; void* saveVTOTAL; void* saveHSYNC; void* saveHBLANK; void* saveHTOTAL; void* saveDPLL; void* saveFP1; void* saveFP0; void* savePIPESRC; void* savePIPECONF; void* saveDSPCNTR; } ;
struct gma_crtc {size_t pipe; struct psb_intel_crtc_state* crtc_state; } ;
struct drm_psb_private {struct psb_offset* regmap; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 void* REG_READ (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 

void gma_crtc_save(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);
	struct psb_intel_crtc_state *crtc_state = gma_crtc->crtc_state;
	const struct psb_offset *map = &dev_priv->regmap[gma_crtc->pipe];
	uint32_t palette_reg;
	int i;

	if (!crtc_state) {
		dev_err(dev->dev, "No CRTC state found\n");
		return;
	}

	crtc_state->saveDSPCNTR = REG_READ(map->cntr);
	crtc_state->savePIPECONF = REG_READ(map->conf);
	crtc_state->savePIPESRC = REG_READ(map->src);
	crtc_state->saveFP0 = REG_READ(map->fp0);
	crtc_state->saveFP1 = REG_READ(map->fp1);
	crtc_state->saveDPLL = REG_READ(map->dpll);
	crtc_state->saveHTOTAL = REG_READ(map->htotal);
	crtc_state->saveHBLANK = REG_READ(map->hblank);
	crtc_state->saveHSYNC = REG_READ(map->hsync);
	crtc_state->saveVTOTAL = REG_READ(map->vtotal);
	crtc_state->saveVBLANK = REG_READ(map->vblank);
	crtc_state->saveVSYNC = REG_READ(map->vsync);
	crtc_state->saveDSPSTRIDE = REG_READ(map->stride);

	/* NOTE: DSPSIZE DSPPOS only for psb */
	crtc_state->saveDSPSIZE = REG_READ(map->size);
	crtc_state->saveDSPPOS = REG_READ(map->pos);

	crtc_state->saveDSPBASE = REG_READ(map->base);

	palette_reg = map->palette;
	for (i = 0; i < 256; ++i)
		crtc_state->savePalette[i] = REG_READ(palette_reg + (i << 2));
}