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
typedef  scalar_t__ uint32_t ;
struct pwl_float_data_ex {int /*<<< orphan*/  r; int /*<<< orphan*/  b; int /*<<< orphan*/  g; } ;
struct hw_x_point {int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_hlg_eotf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void build_hlg_degamma(struct pwl_float_data_ex *degamma,
		uint32_t hw_points_num,
		const struct hw_x_point *coordinate_x,
		uint32_t sdr_white_level, uint32_t max_luminance_nits)
{
	uint32_t i;

	struct pwl_float_data_ex *rgb = degamma;
	const struct hw_x_point *coord_x = coordinate_x;

	i = 0;
	//check when i == 434
	while (i != hw_points_num + 1) {
		compute_hlg_eotf(coord_x->x, &rgb->r, sdr_white_level, max_luminance_nits);
		rgb->g = rgb->r;
		rgb->b = rgb->r;
		++coord_x;
		++rgb;
		++i;
	}
}