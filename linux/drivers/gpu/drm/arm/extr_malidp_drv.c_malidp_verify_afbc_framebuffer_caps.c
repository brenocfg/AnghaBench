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
struct drm_mode_fb_cmd2 {int* modifier; scalar_t__* offsets; int width; int height; int /*<<< orphan*/  pixel_format; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
#define  AFBC_SIZE_16X16 128 
 int AFBC_SIZE_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int malidp_format_mod_supported (struct drm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
malidp_verify_afbc_framebuffer_caps(struct drm_device *dev,
				    const struct drm_mode_fb_cmd2 *mode_cmd)
{
	if (malidp_format_mod_supported(dev, mode_cmd->pixel_format,
					mode_cmd->modifier[0]) == false)
		return false;

	if (mode_cmd->offsets[0] != 0) {
		DRM_DEBUG_KMS("AFBC buffers' plane offset should be 0\n");
		return false;
	}

	switch (mode_cmd->modifier[0] & AFBC_SIZE_MASK) {
	case AFBC_SIZE_16X16:
		if ((mode_cmd->width % 16) || (mode_cmd->height % 16)) {
			DRM_DEBUG_KMS("AFBC buffers must be aligned to 16 pixels\n");
			return false;
		}
		break;
	default:
		DRM_DEBUG_KMS("Unsupported AFBC block size\n");
		return false;
	}

	return true;
}