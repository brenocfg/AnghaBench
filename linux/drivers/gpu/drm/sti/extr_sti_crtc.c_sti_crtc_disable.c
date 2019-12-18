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
struct sti_mixer {scalar_t__ id; int /*<<< orphan*/  status; struct device* dev; } ;
struct sti_compositor {int /*<<< orphan*/  clk_compo_aux; int /*<<< orphan*/  clk_pix_aux; int /*<<< orphan*/  clk_compo_main; int /*<<< orphan*/  clk_pix_main; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_1__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STI_MIXER_DISABLED ; 
 scalar_t__ STI_MIXER_MAIN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sti_compositor* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  sti_mixer_set_background_status (struct sti_mixer*,int) ; 
 int /*<<< orphan*/  sti_mixer_to_str (struct sti_mixer*) ; 
 struct sti_mixer* to_sti_mixer (struct drm_crtc*) ; 

__attribute__((used)) static void sti_crtc_disable(struct drm_crtc *crtc)
{
	struct sti_mixer *mixer = to_sti_mixer(crtc);
	struct device *dev = mixer->dev;
	struct sti_compositor *compo = dev_get_drvdata(dev);

	DRM_DEBUG_KMS("CRTC:%d (%s)\n", crtc->base.id, sti_mixer_to_str(mixer));

	/* Disable Background */
	sti_mixer_set_background_status(mixer, false);

	drm_crtc_vblank_off(crtc);

	/* Disable pixel clock and compo IP clocks */
	if (mixer->id == STI_MIXER_MAIN) {
		clk_disable_unprepare(compo->clk_pix_main);
		clk_disable_unprepare(compo->clk_compo_main);
	} else {
		clk_disable_unprepare(compo->clk_pix_aux);
		clk_disable_unprepare(compo->clk_compo_aux);
	}

	mixer->status = STI_MIXER_DISABLED;
}