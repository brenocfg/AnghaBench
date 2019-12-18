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
struct dce_transform {int dummy; } ;
typedef  enum dcp_spatial_dither_mode { ____Placeholder_dcp_spatial_dither_mode } dcp_spatial_dither_mode ;
typedef  enum dcp_spatial_dither_depth { ____Placeholder_dcp_spatial_dither_depth } dcp_spatial_dither_depth ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  DCP_FRAME_RANDOM_ENABLE ; 
 int /*<<< orphan*/  DCP_HIGHPASS_RANDOM_ENABLE ; 
 int /*<<< orphan*/  DCP_RGB_RANDOM_ENABLE ; 
 int /*<<< orphan*/  DCP_SPATIAL_DITHER_CNTL ; 
 int /*<<< orphan*/  DCP_SPATIAL_DITHER_DEPTH ; 
#define  DCP_SPATIAL_DITHER_DEPTH_24BPP 133 
#define  DCP_SPATIAL_DITHER_DEPTH_30BPP 132 
 int /*<<< orphan*/  DCP_SPATIAL_DITHER_EN ; 
 int /*<<< orphan*/  DCP_SPATIAL_DITHER_MODE ; 
#define  DCP_SPATIAL_DITHER_MODE_AAAA 131 
#define  DCP_SPATIAL_DITHER_MODE_AABBAABB 130 
#define  DCP_SPATIAL_DITHER_MODE_AABBCCAABBCC 129 
#define  DCP_SPATIAL_DITHER_MODE_A_AA_A 128 
 int /*<<< orphan*/  REG_SET_6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_dither(
	struct dce_transform *xfm_dce,
	bool dither_enable,
	enum dcp_spatial_dither_mode dither_mode,
	enum dcp_spatial_dither_depth dither_depth,
	bool frame_random_enable,
	bool rgb_random_enable,
	bool highpass_random_enable)
{
	int dither_depth_bits = 0;
	int dither_mode_bits = 0;

	switch (dither_mode) {
	case DCP_SPATIAL_DITHER_MODE_AAAA:
		dither_mode_bits = 0;
		break;
	case DCP_SPATIAL_DITHER_MODE_A_AA_A:
		dither_mode_bits = 1;
		break;
	case DCP_SPATIAL_DITHER_MODE_AABBAABB:
		dither_mode_bits = 2;
		break;
	case DCP_SPATIAL_DITHER_MODE_AABBCCAABBCC:
		dither_mode_bits = 3;
		break;
	default:
		/* Invalid dcp_spatial_dither_mode */
		BREAK_TO_DEBUGGER();
	}

	switch (dither_depth) {
	case DCP_SPATIAL_DITHER_DEPTH_30BPP:
		dither_depth_bits = 0;
		break;
	case DCP_SPATIAL_DITHER_DEPTH_24BPP:
		dither_depth_bits = 1;
		break;
	default:
		/* Invalid dcp_spatial_dither_depth */
		BREAK_TO_DEBUGGER();
	}

	/*  write the register */
	REG_SET_6(DCP_SPATIAL_DITHER_CNTL, 0,
			DCP_SPATIAL_DITHER_EN, dither_enable,
			DCP_SPATIAL_DITHER_MODE, dither_mode_bits,
			DCP_SPATIAL_DITHER_DEPTH, dither_depth_bits,
			DCP_FRAME_RANDOM_ENABLE, frame_random_enable,
			DCP_RGB_RANDOM_ENABLE, rgb_random_enable,
			DCP_HIGHPASS_RANDOM_ENABLE, highpass_random_enable);
}