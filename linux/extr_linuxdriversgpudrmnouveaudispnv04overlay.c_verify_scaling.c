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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,...) ; 
 int ERANGE ; 

__attribute__((used)) static int
verify_scaling(const struct drm_framebuffer *fb, uint8_t shift,
               uint32_t src_x, uint32_t src_y, uint32_t src_w, uint32_t src_h,
               uint32_t crtc_w, uint32_t crtc_h)
{
	if (crtc_w < (src_w >> shift) || crtc_h < (src_h >> shift)) {
		DRM_DEBUG_KMS("Unsuitable framebuffer scaling: %dx%d -> %dx%d\n",
			      src_w, src_h, crtc_w, crtc_h);
		return -ERANGE;
	}

	if (src_x != 0 || src_y != 0) {
		DRM_DEBUG_KMS("Unsuitable framebuffer offset: %d,%d\n",
                              src_x, src_y);
		return -ERANGE;
	}

	return 0;
}