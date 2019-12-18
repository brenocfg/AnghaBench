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
struct mdp4_kms {int /*<<< orphan*/  base; } ;
struct mdp4_dsi_encoder {int enabled; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDP4_IRQ_PRIMARY_VSYNC ; 
 int /*<<< orphan*/  REG_MDP4_DSI_ENABLE ; 
 struct mdp4_kms* get_kms (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp_irq_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mdp4_dsi_encoder* to_mdp4_dsi_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void mdp4_dsi_encoder_disable(struct drm_encoder *encoder)
{
	struct mdp4_dsi_encoder *mdp4_dsi_encoder = to_mdp4_dsi_encoder(encoder);
	struct mdp4_kms *mdp4_kms = get_kms(encoder);

	if (!mdp4_dsi_encoder->enabled)
		return;

	mdp4_write(mdp4_kms, REG_MDP4_DSI_ENABLE, 0);

	/*
	 * Wait for a vsync so we know the ENABLE=0 latched before
	 * the (connector) source of the vsync's gets disabled,
	 * otherwise we end up in a funny state if we re-enable
	 * before the disable latches, which results that some of
	 * the settings changes for the new modeset (like new
	 * scanout buffer) don't latch properly..
	 */
	mdp_irq_wait(&mdp4_kms->base, MDP4_IRQ_PRIMARY_VSYNC);

	mdp4_dsi_encoder->enabled = false;
}