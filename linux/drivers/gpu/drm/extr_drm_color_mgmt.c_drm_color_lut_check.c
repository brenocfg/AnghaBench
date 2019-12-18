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
typedef  int u32 ;
struct drm_property_blob {struct drm_color_lut* data; } ;
struct drm_color_lut {scalar_t__ red; scalar_t__ blue; scalar_t__ green; } ;

/* Variables and functions */
 int DRM_COLOR_LUT_EQUAL_CHANNELS ; 
 int DRM_COLOR_LUT_NON_DECREASING ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EINVAL ; 
 int drm_color_lut_size (struct drm_property_blob const*) ; 

int drm_color_lut_check(const struct drm_property_blob *lut, u32 tests)
{
	const struct drm_color_lut *entry;
	int i;

	if (!lut || !tests)
		return 0;

	entry = lut->data;
	for (i = 0; i < drm_color_lut_size(lut); i++) {
		if (tests & DRM_COLOR_LUT_EQUAL_CHANNELS) {
			if (entry[i].red != entry[i].blue ||
			    entry[i].red != entry[i].green) {
				DRM_DEBUG_KMS("All LUT entries must have equal r/g/b\n");
				return -EINVAL;
			}
		}

		if (i > 0 && tests & DRM_COLOR_LUT_NON_DECREASING) {
			if (entry[i].red < entry[i - 1].red ||
			    entry[i].green < entry[i - 1].green ||
			    entry[i].blue < entry[i - 1].blue) {
				DRM_DEBUG_KMS("LUT entries must never decrease.\n");
				return -EINVAL;
			}
		}
	}

	return 0;
}