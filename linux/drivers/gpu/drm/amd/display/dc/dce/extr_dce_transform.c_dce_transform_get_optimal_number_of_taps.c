#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct transform {int dummy; } ;
struct scaling_taps {int v_taps; int h_taps; } ;
struct TYPE_10__ {int v_taps; int v_taps_c; void* h_taps_c; void* h_taps; } ;
struct TYPE_9__ {int /*<<< orphan*/  vert_c; int /*<<< orphan*/  vert; int /*<<< orphan*/  horz_c; int /*<<< orphan*/  horz; } ;
struct TYPE_8__ {int /*<<< orphan*/  depth; } ;
struct TYPE_7__ {int width; } ;
struct TYPE_6__ {int width; } ;
struct scaler_data {TYPE_5__ taps; TYPE_4__ ratios; TYPE_3__ lb_params; TYPE_2__ recout; TYPE_1__ viewport; } ;
struct dce_transform {scalar_t__ prescaler_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDENTITY_RATIO (int /*<<< orphan*/ ) ; 
 struct dce_transform* TO_DCE_TRANSFORM (struct transform*) ; 
 int dce_transform_get_max_num_of_supported_lines (struct dce_transform*,int /*<<< orphan*/ ,int) ; 
 void* decide_taps (int /*<<< orphan*/ ,int,int) ; 

bool dce_transform_get_optimal_number_of_taps(
	struct transform *xfm,
	struct scaler_data *scl_data,
	const struct scaling_taps *in_taps)
{
	struct dce_transform *xfm_dce = TO_DCE_TRANSFORM(xfm);
	int pixel_width = scl_data->viewport.width;
	int max_num_of_lines;

	if (xfm_dce->prescaler_on &&
			(scl_data->viewport.width > scl_data->recout.width))
		pixel_width = scl_data->recout.width;

	max_num_of_lines = dce_transform_get_max_num_of_supported_lines(
		xfm_dce,
		scl_data->lb_params.depth,
		pixel_width);

	/* Fail if in_taps are impossible */
	if (in_taps->v_taps >= max_num_of_lines)
		return false;

	/*
	 * Set taps according to this policy (in this order)
	 * - Use 1 for no scaling
	 * - Use input taps
	 * - Use 4 and reduce as required by line buffer size
	 * - Decide chroma taps if chroma is scaled
	 *
	 * Ignore input chroma taps. Decide based on non-chroma
	 */
	scl_data->taps.h_taps = decide_taps(scl_data->ratios.horz, in_taps->h_taps, false);
	scl_data->taps.v_taps = decide_taps(scl_data->ratios.vert, in_taps->v_taps, false);
	scl_data->taps.h_taps_c = decide_taps(scl_data->ratios.horz_c, in_taps->h_taps, true);
	scl_data->taps.v_taps_c = decide_taps(scl_data->ratios.vert_c, in_taps->v_taps, true);

	if (!IDENTITY_RATIO(scl_data->ratios.vert)) {
		/* reduce v_taps if needed but ensure we have at least two */
		if (in_taps->v_taps == 0
				&& max_num_of_lines <= scl_data->taps.v_taps
				&& scl_data->taps.v_taps > 1) {
			scl_data->taps.v_taps = max_num_of_lines - 1;
		}

		if (scl_data->taps.v_taps <= 1)
			return false;
	}

	if (!IDENTITY_RATIO(scl_data->ratios.vert_c)) {
		/* reduce chroma v_taps if needed but ensure we have at least two */
		if (max_num_of_lines <= scl_data->taps.v_taps_c && scl_data->taps.v_taps_c > 1) {
			scl_data->taps.v_taps_c = max_num_of_lines - 1;
		}

		if (scl_data->taps.v_taps_c <= 1)
			return false;
	}

	/* we've got valid taps */
	return true;
}