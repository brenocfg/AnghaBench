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
struct sunxi_engine {TYPE_1__* ops; } ;
struct sun4i_tcon {int /*<<< orphan*/  regs; struct sun4i_crtc* crtc; struct drm_device* drm; } ;
struct sun4i_crtc {int /*<<< orphan*/  crtc; struct sunxi_engine* engine; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* vblank_quirk ) (struct sunxi_engine*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SUN4I_TCON_GINT0_REG ; 
 unsigned int SUN4I_TCON_GINT0_TCON0_TRI_FINISH_INT ; 
 unsigned int SUN4I_TCON_GINT0_VBLANK_INT (int) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sunxi_engine*) ; 
 int /*<<< orphan*/  sun4i_tcon_finish_page_flip (struct drm_device*,struct sun4i_crtc*) ; 

__attribute__((used)) static irqreturn_t sun4i_tcon_handler(int irq, void *private)
{
	struct sun4i_tcon *tcon = private;
	struct drm_device *drm = tcon->drm;
	struct sun4i_crtc *scrtc = tcon->crtc;
	struct sunxi_engine *engine = scrtc->engine;
	unsigned int status;

	regmap_read(tcon->regs, SUN4I_TCON_GINT0_REG, &status);

	if (!(status & (SUN4I_TCON_GINT0_VBLANK_INT(0) |
			SUN4I_TCON_GINT0_VBLANK_INT(1) |
			SUN4I_TCON_GINT0_TCON0_TRI_FINISH_INT)))
		return IRQ_NONE;

	drm_crtc_handle_vblank(&scrtc->crtc);
	sun4i_tcon_finish_page_flip(drm, scrtc);

	/* Acknowledge the interrupt */
	regmap_update_bits(tcon->regs, SUN4I_TCON_GINT0_REG,
			   SUN4I_TCON_GINT0_VBLANK_INT(0) |
			   SUN4I_TCON_GINT0_VBLANK_INT(1) |
			   SUN4I_TCON_GINT0_TCON0_TRI_FINISH_INT,
			   0);

	if (engine->ops->vblank_quirk)
		engine->ops->vblank_quirk(engine);

	return IRQ_HANDLED;
}