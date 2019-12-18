#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct scaling_taps {int h_taps; int v_taps; int v_taps_c; int h_taps_c; } ;
struct TYPE_18__ {int h_taps; int v_taps; int v_taps_c; int h_taps_c; } ;
struct TYPE_19__ {long long value; } ;
struct TYPE_17__ {TYPE_9__ vert_c; TYPE_9__ horz_c; TYPE_9__ vert; TYPE_9__ horz; } ;
struct TYPE_13__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_11__ {scalar_t__ width; } ;
struct scaler_data {scalar_t__ h_active; scalar_t__ v_active; scalar_t__ format; TYPE_8__ taps; TYPE_7__ ratios; TYPE_3__ viewport; TYPE_1__ recout; } ;
struct dpp {TYPE_6__* ctx; TYPE_2__* caps; } ;
struct TYPE_16__ {TYPE_5__* dc; } ;
struct TYPE_14__ {scalar_t__ max_downscale_src_width; int /*<<< orphan*/  always_scale; } ;
struct TYPE_15__ {TYPE_4__ debug; } ;
struct TYPE_12__ {scalar_t__ dscl_data_proc_format; } ;

/* Variables and functions */
 scalar_t__ DSCL_DATA_PRCESSING_FIXED_FORMAT ; 
 scalar_t__ IDENTITY_RATIO (TYPE_9__) ; 
 scalar_t__ PIXEL_FORMAT_FP16 ; 
 int dc_fixpt_ceil (TYPE_9__) ; 

bool dpp2_get_optimal_number_of_taps(
		struct dpp *dpp,
		struct scaler_data *scl_data,
		const struct scaling_taps *in_taps)
{
	uint32_t pixel_width;

	if (scl_data->viewport.width > scl_data->recout.width)
		pixel_width = scl_data->recout.width;
	else
		pixel_width = scl_data->viewport.width;

	/* Some ASICs does not support  FP16 scaling, so we reject modes require this*/
	if (scl_data->viewport.width  != scl_data->h_active &&
		scl_data->viewport.height != scl_data->v_active &&
		dpp->caps->dscl_data_proc_format == DSCL_DATA_PRCESSING_FIXED_FORMAT &&
		scl_data->format == PIXEL_FORMAT_FP16)
		return false;

	if (scl_data->viewport.width > scl_data->h_active &&
		dpp->ctx->dc->debug.max_downscale_src_width != 0 &&
		scl_data->viewport.width > dpp->ctx->dc->debug.max_downscale_src_width)
		return false;

	/* TODO: add lb check */

	/* No support for programming ratio of 8, drop to 7.99999.. */
	if (scl_data->ratios.horz.value == (8ll << 32))
		scl_data->ratios.horz.value--;
	if (scl_data->ratios.vert.value == (8ll << 32))
		scl_data->ratios.vert.value--;
	if (scl_data->ratios.horz_c.value == (8ll << 32))
		scl_data->ratios.horz_c.value--;
	if (scl_data->ratios.vert_c.value == (8ll << 32))
		scl_data->ratios.vert_c.value--;

	/* Set default taps if none are provided */
	if (in_taps->h_taps == 0) {
		if (dc_fixpt_ceil(scl_data->ratios.horz) > 4)
			scl_data->taps.h_taps = 8;
		else
			scl_data->taps.h_taps = 4;
	} else
		scl_data->taps.h_taps = in_taps->h_taps;
	if (in_taps->v_taps == 0) {
		if (dc_fixpt_ceil(scl_data->ratios.vert) > 4)
			scl_data->taps.v_taps = 8;
		else
			scl_data->taps.v_taps = 4;
	} else
		scl_data->taps.v_taps = in_taps->v_taps;
	if (in_taps->v_taps_c == 0) {
		if (dc_fixpt_ceil(scl_data->ratios.vert_c) > 4)
			scl_data->taps.v_taps_c = 4;
		else
			scl_data->taps.v_taps_c = 2;
	} else
		scl_data->taps.v_taps_c = in_taps->v_taps_c;
	if (in_taps->h_taps_c == 0) {
		if (dc_fixpt_ceil(scl_data->ratios.horz_c) > 4)
			scl_data->taps.h_taps_c = 4;
		else
			scl_data->taps.h_taps_c = 2;
	} else if ((in_taps->h_taps_c % 2) != 0 && in_taps->h_taps_c != 1)
		/* Only 1 and even h_taps_c are supported by hw */
		scl_data->taps.h_taps_c = in_taps->h_taps_c - 1;
	else
		scl_data->taps.h_taps_c = in_taps->h_taps_c;

	if (!dpp->ctx->dc->debug.always_scale) {
		if (IDENTITY_RATIO(scl_data->ratios.horz))
			scl_data->taps.h_taps = 1;
		if (IDENTITY_RATIO(scl_data->ratios.vert))
			scl_data->taps.v_taps = 1;
		if (IDENTITY_RATIO(scl_data->ratios.horz_c))
			scl_data->taps.h_taps_c = 1;
		if (IDENTITY_RATIO(scl_data->ratios.vert_c))
			scl_data->taps.v_taps_c = 1;
	}

	return true;
}