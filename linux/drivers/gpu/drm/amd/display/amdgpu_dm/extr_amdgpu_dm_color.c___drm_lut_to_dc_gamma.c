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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_color_lut {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_2__ {void** blue; void** green; void** red; } ;
struct dc_gamma {TYPE_1__ entries; } ;

/* Variables and functions */
 int MAX_COLOR_LEGACY_LUT_ENTRIES ; 
 int MAX_COLOR_LUT_ENTRIES ; 
 int /*<<< orphan*/  MAX_DRM_LUT_VALUE ; 
 void* dc_fixpt_from_fraction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dc_fixpt_from_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_color_lut_extract (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __drm_lut_to_dc_gamma(const struct drm_color_lut *lut,
				  struct dc_gamma *gamma, bool is_legacy)
{
	uint32_t r, g, b;
	int i;

	if (is_legacy) {
		for (i = 0; i < MAX_COLOR_LEGACY_LUT_ENTRIES; i++) {
			r = drm_color_lut_extract(lut[i].red, 16);
			g = drm_color_lut_extract(lut[i].green, 16);
			b = drm_color_lut_extract(lut[i].blue, 16);

			gamma->entries.red[i] = dc_fixpt_from_int(r);
			gamma->entries.green[i] = dc_fixpt_from_int(g);
			gamma->entries.blue[i] = dc_fixpt_from_int(b);
		}
		return;
	}

	/* else */
	for (i = 0; i < MAX_COLOR_LUT_ENTRIES; i++) {
		r = drm_color_lut_extract(lut[i].red, 16);
		g = drm_color_lut_extract(lut[i].green, 16);
		b = drm_color_lut_extract(lut[i].blue, 16);

		gamma->entries.red[i] = dc_fixpt_from_fraction(r, MAX_DRM_LUT_VALUE);
		gamma->entries.green[i] = dc_fixpt_from_fraction(g, MAX_DRM_LUT_VALUE);
		gamma->entries.blue[i] = dc_fixpt_from_fraction(b, MAX_DRM_LUT_VALUE);
	}
}