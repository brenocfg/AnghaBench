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
struct nv04_mode_state {int sel_clk; int pllsel; struct nv04_crtc_reg* crtc_reg; } ;
struct nv04_crtc_reg {int /*<<< orphan*/  gpio_ext; int /*<<< orphan*/ * CRTC; } ;
struct nouveau_crtc {size_t index; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_2__ {struct nv04_mode_state saved_reg; struct nv04_mode_state mode_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVSetOwner (struct drm_device*,size_t) ; 
 size_t NV_CIO_CRE_LCD__INDEX ; 
 int PLLSEL_TV_MASK ; 
 int PLLSEL_VPLL1_MASK ; 
 int PLLSEL_VPLL2_MASK ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  nouveau_hw_save_state (struct drm_device*,size_t,struct nv04_mode_state*) ; 
 TYPE_1__* nv04_display (struct drm_device*) ; 
 scalar_t__ nv_two_heads (struct drm_device*) ; 

__attribute__((used)) static void nv_crtc_save(struct drm_crtc *crtc)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct nv04_mode_state *state = &nv04_display(dev)->mode_reg;
	struct nv04_crtc_reg *crtc_state = &state->crtc_reg[nv_crtc->index];
	struct nv04_mode_state *saved = &nv04_display(dev)->saved_reg;
	struct nv04_crtc_reg *crtc_saved = &saved->crtc_reg[nv_crtc->index];

	if (nv_two_heads(crtc->dev))
		NVSetOwner(crtc->dev, nv_crtc->index);

	nouveau_hw_save_state(crtc->dev, nv_crtc->index, saved);

	/* init some state to saved value */
	state->sel_clk = saved->sel_clk & ~(0x5 << 16);
	crtc_state->CRTC[NV_CIO_CRE_LCD__INDEX] = crtc_saved->CRTC[NV_CIO_CRE_LCD__INDEX];
	state->pllsel = saved->pllsel & ~(PLLSEL_VPLL1_MASK | PLLSEL_VPLL2_MASK | PLLSEL_TV_MASK);
	crtc_state->gpio_ext = crtc_saved->gpio_ext;
}