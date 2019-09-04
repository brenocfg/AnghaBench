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
struct dce_transform {int dummy; } ;
struct TYPE_2__ {int SPATIAL_DITHER_ENABLED; int TRUNCATE_DEPTH; int /*<<< orphan*/  HIGHPASS_RANDOM; int /*<<< orphan*/  RGB_RANDOM; int /*<<< orphan*/  FRAME_RANDOM; scalar_t__ TRUNCATE_MODE; scalar_t__ TRUNCATE_ENABLED; } ;
struct bit_depth_reduction_params {TYPE_1__ flags; } ;
typedef  enum dcp_out_trunc_round_mode { ____Placeholder_dcp_out_trunc_round_mode } dcp_out_trunc_round_mode ;
typedef  enum dcp_out_trunc_round_depth { ____Placeholder_dcp_out_trunc_round_depth } dcp_out_trunc_round_depth ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int COLOR_DEPTH_121212 ; 
 int DCP_OUT_TRUNC_ROUND_DEPTH_10BIT ; 
 int DCP_OUT_TRUNC_ROUND_DEPTH_12BIT ; 
 int DCP_OUT_TRUNC_ROUND_DEPTH_8BIT ; 
 int DCP_OUT_TRUNC_ROUND_MODE_ROUND ; 
 int DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE ; 
 int /*<<< orphan*/  DCP_SPATIAL_DITHER_DEPTH_30BPP ; 
 int /*<<< orphan*/  DCP_SPATIAL_DITHER_MODE_A_AA_A ; 
 int /*<<< orphan*/  set_clamp (struct dce_transform*,int) ; 
 int /*<<< orphan*/  set_dither (struct dce_transform*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_round (struct dce_transform*,int,int) ; 

__attribute__((used)) static void program_bit_depth_reduction(
	struct dce_transform *xfm_dce,
	enum dc_color_depth depth,
	const struct bit_depth_reduction_params *bit_depth_params)
{
	enum dcp_out_trunc_round_depth trunc_round_depth;
	enum dcp_out_trunc_round_mode trunc_mode;
	bool spatial_dither_enable;

	ASSERT(depth < COLOR_DEPTH_121212); /* Invalid clamp bit depth */

	spatial_dither_enable = bit_depth_params->flags.SPATIAL_DITHER_ENABLED;
	/* Default to 12 bit truncation without rounding */
	trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_12BIT;
	trunc_mode = DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE;

	if (bit_depth_params->flags.TRUNCATE_ENABLED) {
		/* Don't enable dithering if truncation is enabled */
		spatial_dither_enable = false;
		trunc_mode = bit_depth_params->flags.TRUNCATE_MODE ?
			     DCP_OUT_TRUNC_ROUND_MODE_ROUND :
			     DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE;

		if (bit_depth_params->flags.TRUNCATE_DEPTH == 0 ||
		    bit_depth_params->flags.TRUNCATE_DEPTH == 1)
			trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_8BIT;
		else if (bit_depth_params->flags.TRUNCATE_DEPTH == 2)
			trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_10BIT;
		else {
			/*
			 * Invalid truncate/round depth. Setting here to 12bit
			 * to prevent use-before-initialize errors.
			 */
			trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_12BIT;
			BREAK_TO_DEBUGGER();
		}
	}

	set_clamp(xfm_dce, depth);
	set_round(xfm_dce, trunc_mode, trunc_round_depth);
	set_dither(xfm_dce,
		   spatial_dither_enable,
		   DCP_SPATIAL_DITHER_MODE_A_AA_A,
		   DCP_SPATIAL_DITHER_DEPTH_30BPP,
		   bit_depth_params->flags.FRAME_RANDOM,
		   bit_depth_params->flags.RGB_RANDOM,
		   bit_depth_params->flags.HIGHPASS_RANDOM);
}