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
typedef  int uint32_t ;
struct drm_color_lut {scalar_t__ red; scalar_t__ green; scalar_t__ blue; } ;

/* Variables and functions */
 int MAX_DRM_LUT_VALUE ; 

__attribute__((used)) static bool __is_lut_linear(struct drm_color_lut *lut, uint32_t size)
{
	int i;
	uint32_t expected;
	int delta;

	for (i = 0; i < size; i++) {
		/* All color values should equal */
		if ((lut[i].red != lut[i].green) || (lut[i].green != lut[i].blue))
			return false;

		expected = i * MAX_DRM_LUT_VALUE / (size-1);

		/* Allow a +/-1 error. */
		delta = lut[i].red - expected;
		if (delta < -1 || 1 < delta)
			return false;
	}
	return true;
}