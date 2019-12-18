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
typedef  int u32 ;
struct drm_property_blob {scalar_t__ data; } ;
struct drm_color_lut {int /*<<< orphan*/  green; } ;
struct TYPE_2__ {int end; int start; } ;

/* Variables and functions */
 int DE_COEFTAB_DATA (int,int) ; 
 int MALIDP_COEFFTAB_NUM_COEFFS ; 
 int drm_color_lut_extract (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* segments ; 

__attribute__((used)) static void malidp_generate_gamma_table(struct drm_property_blob *lut_blob,
					u32 coeffs[MALIDP_COEFFTAB_NUM_COEFFS])
{
	struct drm_color_lut *lut = (struct drm_color_lut *)lut_blob->data;
	int i;

	for (i = 0; i < MALIDP_COEFFTAB_NUM_COEFFS; ++i) {
		u32 a, b, delta_in, out_start, out_end;

		delta_in = segments[i].end - segments[i].start;
		/* DP has 12-bit internal precision for its LUTs. */
		out_start = drm_color_lut_extract(lut[segments[i].start].green,
						  12);
		out_end = drm_color_lut_extract(lut[segments[i].end].green, 12);
		a = (delta_in == 0) ? 0 : ((out_end - out_start) * 256) / delta_in;
		b = out_start;
		coeffs[i] = DE_COEFTAB_DATA(a, b);
	}
}