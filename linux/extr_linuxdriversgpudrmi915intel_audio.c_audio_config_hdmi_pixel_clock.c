#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct drm_display_mode {scalar_t__ crtc_clock; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct TYPE_5__ {scalar_t__ clock; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__,...) ; 
 TYPE_2__* hdmi_audio_clock ; 

__attribute__((used)) static u32 audio_config_hdmi_pixel_clock(const struct intel_crtc_state *crtc_state)
{
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;
	int i;

	for (i = 0; i < ARRAY_SIZE(hdmi_audio_clock); i++) {
		if (adjusted_mode->crtc_clock == hdmi_audio_clock[i].clock)
			break;
	}

	if (i == ARRAY_SIZE(hdmi_audio_clock)) {
		DRM_DEBUG_KMS("HDMI audio pixel clock setting for %d not found, falling back to defaults\n",
			      adjusted_mode->crtc_clock);
		i = 1;
	}

	DRM_DEBUG_KMS("Configuring HDMI audio for pixel clock %d (0x%08x)\n",
		      hdmi_audio_clock[i].clock,
		      hdmi_audio_clock[i].config);

	return hdmi_audio_clock[i].config;
}