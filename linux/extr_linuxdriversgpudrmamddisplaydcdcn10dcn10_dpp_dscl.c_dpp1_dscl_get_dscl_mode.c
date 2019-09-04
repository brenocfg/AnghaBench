#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {long long const value; } ;
struct TYPE_11__ {long long const value; } ;
struct TYPE_10__ {long long const value; } ;
struct TYPE_9__ {long long const value; } ;
struct TYPE_13__ {TYPE_5__ vert_c; TYPE_4__ horz_c; TYPE_3__ vert; TYPE_2__ horz; } ;
struct scaler_data {scalar_t__ format; TYPE_6__ ratios; } ;
struct dpp {TYPE_1__* caps; } ;
typedef  enum dscl_mode_sel { ____Placeholder_dscl_mode_sel } dscl_mode_sel ;
struct TYPE_14__ {long long value; } ;
struct TYPE_8__ {scalar_t__ dscl_data_proc_format; } ;

/* Variables and functions */
 scalar_t__ DSCL_DATA_PRCESSING_FIXED_FORMAT ; 
 int DSCL_MODE_DSCL_BYPASS ; 
 int DSCL_MODE_SCALING_420_CHROMA_BYPASS ; 
 int DSCL_MODE_SCALING_420_LUMA_BYPASS ; 
 int DSCL_MODE_SCALING_420_YCBCR_ENABLE ; 
 int DSCL_MODE_SCALING_444_BYPASS ; 
 int DSCL_MODE_SCALING_444_RGB_ENABLE ; 
 int DSCL_MODE_SCALING_444_YCBCR_ENABLE ; 
 scalar_t__ PIXEL_FORMAT_FP16 ; 
 TYPE_7__ dc_fixpt_one ; 
 int /*<<< orphan*/  dpp1_dscl_is_420_format (scalar_t__) ; 
 scalar_t__ dpp1_dscl_is_video_format (scalar_t__) ; 

__attribute__((used)) static enum dscl_mode_sel dpp1_dscl_get_dscl_mode(
		struct dpp *dpp_base,
		const struct scaler_data *data,
		bool dbg_always_scale)
{
	const long long one = dc_fixpt_one.value;

	if (dpp_base->caps->dscl_data_proc_format == DSCL_DATA_PRCESSING_FIXED_FORMAT) {
		/* DSCL is processing data in fixed format */
		if (data->format == PIXEL_FORMAT_FP16)
			return DSCL_MODE_DSCL_BYPASS;
	}

	if (data->ratios.horz.value == one
			&& data->ratios.vert.value == one
			&& data->ratios.horz_c.value == one
			&& data->ratios.vert_c.value == one
			&& !dbg_always_scale)
		return DSCL_MODE_SCALING_444_BYPASS;

	if (!dpp1_dscl_is_420_format(data->format)) {
		if (dpp1_dscl_is_video_format(data->format))
			return DSCL_MODE_SCALING_444_YCBCR_ENABLE;
		else
			return DSCL_MODE_SCALING_444_RGB_ENABLE;
	}
	if (data->ratios.horz.value == one && data->ratios.vert.value == one)
		return DSCL_MODE_SCALING_420_LUMA_BYPASS;
	if (data->ratios.horz_c.value == one && data->ratios.vert_c.value == one)
		return DSCL_MODE_SCALING_420_CHROMA_BYPASS;

	return DSCL_MODE_SCALING_420_YCBCR_ENABLE;
}