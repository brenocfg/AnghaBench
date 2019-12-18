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
struct psb_intel_sdvo {int /*<<< orphan*/  input_dtd; } ;
struct drm_display_mode {int clock; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_intel_sdvo_create_preferred_input_timing (struct psb_intel_sdvo*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_intel_sdvo_get_mode_from_dtd (struct drm_display_mode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_intel_sdvo_get_preferred_input_timing (struct psb_intel_sdvo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_intel_sdvo_set_target_input (struct psb_intel_sdvo*) ; 

__attribute__((used)) static bool
psb_intel_sdvo_set_input_timings_for_mode(struct psb_intel_sdvo *psb_intel_sdvo,
					const struct drm_display_mode *mode,
					struct drm_display_mode *adjusted_mode)
{
	/* Reset the input timing to the screen. Assume always input 0. */
	if (!psb_intel_sdvo_set_target_input(psb_intel_sdvo))
		return false;

	if (!psb_intel_sdvo_create_preferred_input_timing(psb_intel_sdvo,
						      mode->clock / 10,
						      mode->hdisplay,
						      mode->vdisplay))
		return false;

	if (!psb_intel_sdvo_get_preferred_input_timing(psb_intel_sdvo,
						   &psb_intel_sdvo->input_dtd))
		return false;

	psb_intel_sdvo_get_mode_from_dtd(adjusted_mode, &psb_intel_sdvo->input_dtd);

	drm_mode_set_crtcinfo(adjusted_mode, 0);
	return true;
}