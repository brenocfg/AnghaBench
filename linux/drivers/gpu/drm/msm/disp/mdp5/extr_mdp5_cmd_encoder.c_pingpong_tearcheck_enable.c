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
struct mdp5_kms {int /*<<< orphan*/  vsync_clk; } ;
struct mdp5_hw_mixer {int pp; } ;
struct drm_encoder {TYPE_1__* dev; int /*<<< orphan*/  crtc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  REG_MDP5_PP_TEAR_CHECK_EN (int) ; 
 int /*<<< orphan*/  VSYNC_CLK_RATE ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_round_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdp5_kms* get_kms (struct drm_encoder*) ; 
 struct mdp5_hw_mixer* mdp5_crtc_get_mixer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pingpong_tearcheck_enable(struct drm_encoder *encoder)
{
	struct mdp5_kms *mdp5_kms = get_kms(encoder);
	struct mdp5_hw_mixer *mixer = mdp5_crtc_get_mixer(encoder->crtc);
	int pp_id = mixer->pp;
	int ret;

	ret = clk_set_rate(mdp5_kms->vsync_clk,
		clk_round_rate(mdp5_kms->vsync_clk, VSYNC_CLK_RATE));
	if (ret) {
		DRM_DEV_ERROR(encoder->dev->dev,
			"vsync_clk clk_set_rate failed, %d\n", ret);
		return ret;
	}
	ret = clk_prepare_enable(mdp5_kms->vsync_clk);
	if (ret) {
		DRM_DEV_ERROR(encoder->dev->dev,
			"vsync_clk clk_prepare_enable failed, %d\n", ret);
		return ret;
	}

	mdp5_write(mdp5_kms, REG_MDP5_PP_TEAR_CHECK_EN(pp_id), 1);

	return 0;
}