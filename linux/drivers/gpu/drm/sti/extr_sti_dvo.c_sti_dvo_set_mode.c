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
struct sti_mixer {scalar_t__ id; } ;
struct sti_dvo {int /*<<< orphan*/ * config; int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_pix; struct clk* clk_aux_parent; struct clk* clk_main_parent; int /*<<< orphan*/  mode; TYPE_1__* encoder; } ;
struct drm_display_mode {int clock; } ;
struct drm_bridge {struct sti_dvo* driver_private; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ STI_MIXER_MAIN ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,struct clk*) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct drm_display_mode const*,int) ; 
 int /*<<< orphan*/  rgb_24bit_de_cfg ; 
 struct sti_mixer* to_sti_mixer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sti_dvo_set_mode(struct drm_bridge *bridge,
			     const struct drm_display_mode *mode,
			     const struct drm_display_mode *adjusted_mode)
{
	struct sti_dvo *dvo = bridge->driver_private;
	struct sti_mixer *mixer = to_sti_mixer(dvo->encoder->crtc);
	int rate = mode->clock * 1000;
	struct clk *clkp;
	int ret;

	DRM_DEBUG_DRIVER("\n");

	memcpy(&dvo->mode, mode, sizeof(struct drm_display_mode));

	/* According to the path used (main or aux), the dvo clocks should
	 * have a different parent clock. */
	if (mixer->id == STI_MIXER_MAIN)
		clkp = dvo->clk_main_parent;
	else
		clkp = dvo->clk_aux_parent;

	if (clkp) {
		clk_set_parent(dvo->clk_pix, clkp);
		clk_set_parent(dvo->clk, clkp);
	}

	/* DVO clocks = compositor clock */
	ret = clk_set_rate(dvo->clk_pix, rate);
	if (ret < 0) {
		DRM_ERROR("Cannot set rate (%dHz) for dvo_pix clk\n", rate);
		return;
	}

	ret = clk_set_rate(dvo->clk, rate);
	if (ret < 0) {
		DRM_ERROR("Cannot set rate (%dHz) for dvo clk\n", rate);
		return;
	}

	/* For now, we only support 24bit data enable (DE) synchro format */
	dvo->config = &rgb_24bit_de_cfg;
}