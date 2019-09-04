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
struct drm_display_mode {scalar_t__ crtc_clock; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct TYPE_5__ {int sample_rate; scalar_t__ clock; int n; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 TYPE_2__* hdmi_aud_ncts ; 

__attribute__((used)) static int audio_config_hdmi_get_n(const struct intel_crtc_state *crtc_state,
				   int rate)
{
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;
	int i;

	for (i = 0; i < ARRAY_SIZE(hdmi_aud_ncts); i++) {
		if (rate == hdmi_aud_ncts[i].sample_rate &&
		    adjusted_mode->crtc_clock == hdmi_aud_ncts[i].clock) {
			return hdmi_aud_ncts[i].n;
		}
	}
	return 0;
}