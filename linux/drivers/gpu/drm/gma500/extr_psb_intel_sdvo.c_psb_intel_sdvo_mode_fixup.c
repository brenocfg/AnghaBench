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
struct psb_intel_sdvo {struct drm_display_mode const* sdvo_lvds_fixed_mode; scalar_t__ is_lvds; scalar_t__ is_tv; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  psb_intel_mode_set_pixel_multiplier (struct drm_display_mode*,int) ; 
 int psb_intel_sdvo_get_pixel_multiplier (struct drm_display_mode*) ; 
 int /*<<< orphan*/  psb_intel_sdvo_set_input_timings_for_mode (struct psb_intel_sdvo*,struct drm_display_mode const*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  psb_intel_sdvo_set_output_timings_from_mode (struct psb_intel_sdvo*,struct drm_display_mode const*) ; 
 struct psb_intel_sdvo* to_psb_intel_sdvo (struct drm_encoder*) ; 

__attribute__((used)) static bool psb_intel_sdvo_mode_fixup(struct drm_encoder *encoder,
				  const struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode)
{
	struct psb_intel_sdvo *psb_intel_sdvo = to_psb_intel_sdvo(encoder);
	int multiplier;

	/* We need to construct preferred input timings based on our
	 * output timings.  To do that, we have to set the output
	 * timings, even though this isn't really the right place in
	 * the sequence to do it. Oh well.
	 */
	if (psb_intel_sdvo->is_tv) {
		if (!psb_intel_sdvo_set_output_timings_from_mode(psb_intel_sdvo, mode))
			return false;

		(void) psb_intel_sdvo_set_input_timings_for_mode(psb_intel_sdvo,
							     mode,
							     adjusted_mode);
	} else if (psb_intel_sdvo->is_lvds) {
		if (!psb_intel_sdvo_set_output_timings_from_mode(psb_intel_sdvo,
							     psb_intel_sdvo->sdvo_lvds_fixed_mode))
			return false;

		(void) psb_intel_sdvo_set_input_timings_for_mode(psb_intel_sdvo,
							     mode,
							     adjusted_mode);
	}

	/* Make the CRTC code factor in the SDVO pixel multiplier.  The
	 * SDVO device will factor out the multiplier during mode_set.
	 */
	multiplier = psb_intel_sdvo_get_pixel_multiplier(adjusted_mode);
	psb_intel_mode_set_pixel_multiplier(adjusted_mode, multiplier);

	return true;
}