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
struct mdp4_lcdc_encoder {int enabled; int /*<<< orphan*/ * regs; int /*<<< orphan*/  lcdc_clk; int /*<<< orphan*/  panel_node; } ;
struct mdp4_kms {int /*<<< orphan*/  base; } ;
struct drm_panel {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IS_ERR (struct drm_panel*) ; 
 int /*<<< orphan*/  MDP4_IRQ_PRIMARY_VSYNC ; 
 int /*<<< orphan*/  REG_MDP4_LCDC_ENABLE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  bs_set (struct mdp4_lcdc_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_disable (struct drm_panel*) ; 
 int /*<<< orphan*/  drm_panel_unprepare (struct drm_panel*) ; 
 struct mdp4_kms* get_kms (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp_irq_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_panel* of_drm_find_panel (int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 struct mdp4_lcdc_encoder* to_mdp4_lcdc_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void mdp4_lcdc_encoder_disable(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct mdp4_lcdc_encoder *mdp4_lcdc_encoder =
			to_mdp4_lcdc_encoder(encoder);
	struct mdp4_kms *mdp4_kms = get_kms(encoder);
	struct drm_panel *panel;
	int i, ret;

	if (WARN_ON(!mdp4_lcdc_encoder->enabled))
		return;

	mdp4_write(mdp4_kms, REG_MDP4_LCDC_ENABLE, 0);

	panel = of_drm_find_panel(mdp4_lcdc_encoder->panel_node);
	if (!IS_ERR(panel)) {
		drm_panel_disable(panel);
		drm_panel_unprepare(panel);
	}

	/*
	 * Wait for a vsync so we know the ENABLE=0 latched before
	 * the (connector) source of the vsync's gets disabled,
	 * otherwise we end up in a funny state if we re-enable
	 * before the disable latches, which results that some of
	 * the settings changes for the new modeset (like new
	 * scanout buffer) don't latch properly..
	 */
	mdp_irq_wait(&mdp4_kms->base, MDP4_IRQ_PRIMARY_VSYNC);

	clk_disable_unprepare(mdp4_lcdc_encoder->lcdc_clk);

	for (i = 0; i < ARRAY_SIZE(mdp4_lcdc_encoder->regs); i++) {
		ret = regulator_disable(mdp4_lcdc_encoder->regs[i]);
		if (ret)
			DRM_DEV_ERROR(dev->dev, "failed to disable regulator: %d\n", ret);
	}

	bs_set(mdp4_lcdc_encoder, 0);

	mdp4_lcdc_encoder->enabled = false;
}