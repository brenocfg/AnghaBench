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
struct fixed31_32 {unsigned long long value; } ;
struct drm_color_ctm {unsigned long long* matrix; } ;
typedef  unsigned long long int64_t ;

/* Variables and functions */
 struct fixed31_32 dc_fixpt_zero ; 

__attribute__((used)) static void __drm_ctm_to_dc_matrix(const struct drm_color_ctm *ctm,
				   struct fixed31_32 *matrix)
{
	int64_t val;
	int i;

	/*
	 * DRM gives a 3x3 matrix, but DC wants 3x4. Assuming we're operating
	 * with homogeneous coordinates, augment the matrix with 0's.
	 *
	 * The format provided is S31.32, using signed-magnitude representation.
	 * Our fixed31_32 is also S31.32, but is using 2's complement. We have
	 * to convert from signed-magnitude to 2's complement.
	 */
	for (i = 0; i < 12; i++) {
		/* Skip 4th element */
		if (i % 4 == 3) {
			matrix[i] = dc_fixpt_zero;
			continue;
		}

		/* gamut_remap_matrix[i] = ctm[i - floor(i/4)] */
		val = ctm->matrix[i - (i / 4)];
		/* If negative, convert to 2's complement. */
		if (val & (1ULL << 63))
			val = -(val & ~(1ULL << 63));

		matrix[i].value = val;
	}
}