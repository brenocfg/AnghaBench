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
struct mdp4_kms {int dummy; } ;
struct mdp4_dsi_encoder {int enabled; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPC8 ; 
 int /*<<< orphan*/  INTF_DSI_VIDEO ; 
 int MDP4_DMA_CONFIG_B_BPC (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_CONFIG_DEFLKR_EN ; 
 int MDP4_DMA_CONFIG_DITHER_EN ; 
 int MDP4_DMA_CONFIG_G_BPC (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_CONFIG_PACK (int) ; 
 int MDP4_DMA_CONFIG_PACK_ALIGN_MSB ; 
 int MDP4_DMA_CONFIG_R_BPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP4_DSI_ENABLE ; 
 struct mdp4_kms* get_kms (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp4_crtc_set_config (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp4_crtc_set_intf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int) ; 
 struct mdp4_dsi_encoder* to_mdp4_dsi_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void mdp4_dsi_encoder_enable(struct drm_encoder *encoder)
{
	struct mdp4_dsi_encoder *mdp4_dsi_encoder = to_mdp4_dsi_encoder(encoder);
	struct mdp4_kms *mdp4_kms = get_kms(encoder);

	if (mdp4_dsi_encoder->enabled)
		return;

	 mdp4_crtc_set_config(encoder->crtc,
			MDP4_DMA_CONFIG_PACK_ALIGN_MSB |
			MDP4_DMA_CONFIG_DEFLKR_EN |
			MDP4_DMA_CONFIG_DITHER_EN |
			MDP4_DMA_CONFIG_R_BPC(BPC8) |
			MDP4_DMA_CONFIG_G_BPC(BPC8) |
			MDP4_DMA_CONFIG_B_BPC(BPC8) |
			MDP4_DMA_CONFIG_PACK(0x21));

	mdp4_crtc_set_intf(encoder->crtc, INTF_DSI_VIDEO, 0);

	mdp4_write(mdp4_kms, REG_MDP4_DSI_ENABLE, 1);

	mdp4_dsi_encoder->enabled = true;
}