#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mdp4_kms {int dummy; } ;
struct mdp4_crtc {int dma; int ovlp; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_display_mode {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; int /*<<< orphan*/  htotal; int /*<<< orphan*/  hsync_end; int /*<<< orphan*/  hsync_start; int /*<<< orphan*/  clock; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  name; TYPE_2__ base; } ;
struct drm_crtc {TYPE_1__* state; } ;
typedef  enum mdp4_dma { ____Placeholder_mdp4_dma } mdp4_dma ;
struct TYPE_3__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DMA_E ; 
 int MDP4_DMA_DST_SIZE_HEIGHT (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_DST_SIZE_WIDTH (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_SRC_SIZE_HEIGHT (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_SRC_SIZE_WIDTH (int /*<<< orphan*/ ) ; 
 int MDP4_OVLP_SIZE_HEIGHT (int /*<<< orphan*/ ) ; 
 int MDP4_OVLP_SIZE_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_DST_SIZE (int) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_E_QUANT (int) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_SRC_BASE (int) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_SRC_SIZE (int) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_SRC_STRIDE (int) ; 
 int /*<<< orphan*/  REG_MDP4_OVLP_BASE (int) ; 
 int /*<<< orphan*/  REG_MDP4_OVLP_CFG (int) ; 
 int /*<<< orphan*/  REG_MDP4_OVLP_SIZE (int) ; 
 int /*<<< orphan*/  REG_MDP4_OVLP_STRIDE (int) ; 
 scalar_t__ WARN_ON (int) ; 
 struct mdp4_kms* get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void mdp4_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	struct mdp4_kms *mdp4_kms = get_kms(crtc);
	enum mdp4_dma dma = mdp4_crtc->dma;
	int ovlp = mdp4_crtc->ovlp;
	struct drm_display_mode *mode;

	if (WARN_ON(!crtc->state))
		return;

	mode = &crtc->state->adjusted_mode;

	DBG("%s: set mode: %d:\"%s\" %d %d %d %d %d %d %d %d %d %d 0x%x 0x%x",
			mdp4_crtc->name, mode->base.id, mode->name,
			mode->vrefresh, mode->clock,
			mode->hdisplay, mode->hsync_start,
			mode->hsync_end, mode->htotal,
			mode->vdisplay, mode->vsync_start,
			mode->vsync_end, mode->vtotal,
			mode->type, mode->flags);

	mdp4_write(mdp4_kms, REG_MDP4_DMA_SRC_SIZE(dma),
			MDP4_DMA_SRC_SIZE_WIDTH(mode->hdisplay) |
			MDP4_DMA_SRC_SIZE_HEIGHT(mode->vdisplay));

	/* take data from pipe: */
	mdp4_write(mdp4_kms, REG_MDP4_DMA_SRC_BASE(dma), 0);
	mdp4_write(mdp4_kms, REG_MDP4_DMA_SRC_STRIDE(dma), 0);
	mdp4_write(mdp4_kms, REG_MDP4_DMA_DST_SIZE(dma),
			MDP4_DMA_DST_SIZE_WIDTH(0) |
			MDP4_DMA_DST_SIZE_HEIGHT(0));

	mdp4_write(mdp4_kms, REG_MDP4_OVLP_BASE(ovlp), 0);
	mdp4_write(mdp4_kms, REG_MDP4_OVLP_SIZE(ovlp),
			MDP4_OVLP_SIZE_WIDTH(mode->hdisplay) |
			MDP4_OVLP_SIZE_HEIGHT(mode->vdisplay));
	mdp4_write(mdp4_kms, REG_MDP4_OVLP_STRIDE(ovlp), 0);

	mdp4_write(mdp4_kms, REG_MDP4_OVLP_CFG(ovlp), 1);

	if (dma == DMA_E) {
		mdp4_write(mdp4_kms, REG_MDP4_DMA_E_QUANT(0), 0x00ff0000);
		mdp4_write(mdp4_kms, REG_MDP4_DMA_E_QUANT(1), 0x00ff0000);
		mdp4_write(mdp4_kms, REG_MDP4_DMA_E_QUANT(2), 0x00ff0000);
	}
}