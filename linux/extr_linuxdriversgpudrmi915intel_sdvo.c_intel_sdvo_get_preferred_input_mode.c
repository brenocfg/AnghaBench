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
struct TYPE_2__ {int /*<<< orphan*/  sdvo_flags; } ;
struct intel_sdvo_dtd {TYPE_1__ part2; } ;
struct intel_sdvo {int /*<<< orphan*/  dtd_sdvo_flags; } ;
struct drm_display_mode {int clock; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_sdvo_create_preferred_input_timing (struct intel_sdvo*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sdvo_get_mode_from_dtd (struct drm_display_mode*,struct intel_sdvo_dtd*) ; 
 int /*<<< orphan*/  intel_sdvo_get_preferred_input_timing (struct intel_sdvo*,struct intel_sdvo_dtd*) ; 
 int /*<<< orphan*/  intel_sdvo_set_target_input (struct intel_sdvo*) ; 

__attribute__((used)) static bool
intel_sdvo_get_preferred_input_mode(struct intel_sdvo *intel_sdvo,
				    const struct drm_display_mode *mode,
				    struct drm_display_mode *adjusted_mode)
{
	struct intel_sdvo_dtd input_dtd;

	/* Reset the input timing to the screen. Assume always input 0. */
	if (!intel_sdvo_set_target_input(intel_sdvo))
		return false;

	if (!intel_sdvo_create_preferred_input_timing(intel_sdvo,
						      mode->clock / 10,
						      mode->hdisplay,
						      mode->vdisplay))
		return false;

	if (!intel_sdvo_get_preferred_input_timing(intel_sdvo,
						   &input_dtd))
		return false;

	intel_sdvo_get_mode_from_dtd(adjusted_mode, &input_dtd);
	intel_sdvo->dtd_sdvo_flags = input_dtd.part2.sdvo_flags;

	return true;
}