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
struct intel_encoder {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 int /*<<< orphan*/  drm_mode_debug_printmodeline (struct drm_display_mode*) ; 
 struct drm_display_mode* intel_encoder_current_mode (struct intel_encoder*) ; 

__attribute__((used)) static struct drm_display_mode *
intel_dvo_get_current_mode(struct intel_encoder *encoder)
{
	struct drm_display_mode *mode;

	mode = intel_encoder_current_mode(encoder);
	if (mode) {
		DRM_DEBUG_KMS("using current (BIOS) mode: ");
		drm_mode_debug_printmodeline(mode);
		mode->type |= DRM_MODE_TYPE_PREFERRED;
	}

	return mode;
}