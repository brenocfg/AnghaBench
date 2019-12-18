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
struct mdp4_dtv_encoder {unsigned long pixclock; int enabled; int /*<<< orphan*/  hdmi_clk; int /*<<< orphan*/  mdp_clk; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPC8 ; 
 int /*<<< orphan*/  DBG (char*,unsigned long) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  INTF_LCDC_DTV ; 
 int MDP4_DMA_CONFIG_B_BPC (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_CONFIG_G_BPC (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_CONFIG_PACK (int) ; 
 int MDP4_DMA_CONFIG_R_BPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP4_DTV_ENABLE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  bs_set (struct mdp4_dtv_encoder*,int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct mdp4_kms* get_kms (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp4_crtc_set_config (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp4_crtc_set_intf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int) ; 
 struct mdp4_dtv_encoder* to_mdp4_dtv_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void mdp4_dtv_encoder_enable(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct mdp4_dtv_encoder *mdp4_dtv_encoder = to_mdp4_dtv_encoder(encoder);
	struct mdp4_kms *mdp4_kms = get_kms(encoder);
	unsigned long pc = mdp4_dtv_encoder->pixclock;
	int ret;

	if (WARN_ON(mdp4_dtv_encoder->enabled))
		return;

	mdp4_crtc_set_config(encoder->crtc,
			MDP4_DMA_CONFIG_R_BPC(BPC8) |
			MDP4_DMA_CONFIG_G_BPC(BPC8) |
			MDP4_DMA_CONFIG_B_BPC(BPC8) |
			MDP4_DMA_CONFIG_PACK(0x21));
	mdp4_crtc_set_intf(encoder->crtc, INTF_LCDC_DTV, 1);

	bs_set(mdp4_dtv_encoder, 1);

	DBG("setting mdp_clk=%lu", pc);

	ret = clk_set_rate(mdp4_dtv_encoder->mdp_clk, pc);
	if (ret)
		DRM_DEV_ERROR(dev->dev, "failed to set mdp_clk to %lu: %d\n",
			pc, ret);

	ret = clk_prepare_enable(mdp4_dtv_encoder->mdp_clk);
	if (ret)
		DRM_DEV_ERROR(dev->dev, "failed to enabled mdp_clk: %d\n", ret);

	ret = clk_prepare_enable(mdp4_dtv_encoder->hdmi_clk);
	if (ret)
		DRM_DEV_ERROR(dev->dev, "failed to enable hdmi_clk: %d\n", ret);

	mdp4_write(mdp4_kms, REG_MDP4_DTV_ENABLE, 1);

	mdp4_dtv_encoder->enabled = true;
}