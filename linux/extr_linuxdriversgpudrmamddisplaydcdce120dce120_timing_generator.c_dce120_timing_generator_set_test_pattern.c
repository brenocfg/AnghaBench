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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct timing_generator {struct dc_context* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct dce110_timing_generator {TYPE_1__ offsets; } ;
struct dc_context {int dummy; } ;
typedef  enum test_pattern_mode { ____Placeholder_test_pattern_mode } test_pattern_mode ;
typedef  enum test_pattern_dyn_range { ____Placeholder_test_pattern_dyn_range } test_pattern_dyn_range ;
typedef  enum test_pattern_color_format { ____Placeholder_test_pattern_color_format } test_pattern_color_format ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;
typedef  enum controller_dp_test_pattern { ____Placeholder_controller_dp_test_pattern } controller_dp_test_pattern ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 140 
#define  COLOR_DEPTH_121212 139 
#define  COLOR_DEPTH_666 138 
#define  COLOR_DEPTH_888 137 
#define  CONTROLLER_DP_TEST_PATTERN_COLORRAMP 136 
#define  CONTROLLER_DP_TEST_PATTERN_COLORSQUARES 135 
#define  CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA 134 
#define  CONTROLLER_DP_TEST_PATTERN_HORIZONTALBARS 133 
#define  CONTROLLER_DP_TEST_PATTERN_VERTICALBARS 132 
#define  CONTROLLER_DP_TEST_PATTERN_VIDEOMODE 131 
 int /*<<< orphan*/  CRTC0_CRTC_TEST_PATTERN_COLOR ; 
 int /*<<< orphan*/  CRTC0_CRTC_TEST_PATTERN_CONTROL ; 
 int /*<<< orphan*/  CRTC0_CRTC_TEST_PATTERN_PARAMETERS ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_COLOR_FORMAT ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_DATA ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_DYNAMIC_RANGE ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_EN ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_HRES ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_INC0 ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_INC1 ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_MASK ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_MODE ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_RAMP0_OFFSET ; 
 int /*<<< orphan*/  CRTC_TEST_PATTERN_VRES ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
#define  TEST_PATTERN_COLOR_FORMAT_BPC_10 130 
 int TEST_PATTERN_COLOR_FORMAT_BPC_12 ; 
#define  TEST_PATTERN_COLOR_FORMAT_BPC_6 129 
#define  TEST_PATTERN_COLOR_FORMAT_BPC_8 128 
 int TEST_PATTERN_DYN_RANGE_CEA ; 
 int TEST_PATTERN_DYN_RANGE_VESA ; 
 int TEST_PATTERN_MODE_COLORSQUARES_RGB ; 
 int TEST_PATTERN_MODE_DUALRAMP_RGB ; 
 int TEST_PATTERN_MODE_HORIZONTALBARS ; 
 int TEST_PATTERN_MODE_SINGLERAMP_RGB ; 
 int TEST_PATTERN_MODE_VERTICALBARS ; 
 int /*<<< orphan*/  dm_write_reg_soc15 (struct dc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_TEST_PATTERN_COLOR ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_TEST_PATTERN_CONTROL ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_TEST_PATTERN_PARAMETERS ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce120_timing_generator_set_test_pattern(
	struct timing_generator *tg,
	/* TODO: replace 'controller_dp_test_pattern' by 'test_pattern_mode'
	 * because this is not DP-specific (which is probably somewhere in DP
	 * encoder) */
	enum controller_dp_test_pattern test_pattern,
	enum dc_color_depth color_depth)
{
	struct dc_context *ctx = tg->ctx;
	uint32_t value;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	enum test_pattern_color_format bit_depth;
	enum test_pattern_dyn_range dyn_range;
	enum test_pattern_mode mode;
	/* color ramp generator mixes 16-bits color */
	uint32_t src_bpc = 16;
	/* requested bpc */
	uint32_t dst_bpc;
	uint32_t index;
	/* RGB values of the color bars.
	 * Produce two RGB colors: RGB0 - white (all Fs)
	 * and RGB1 - black (all 0s)
	 * (three RGB components for two colors)
	 */
	uint16_t src_color[6] = {0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
						0x0000, 0x0000};
	/* dest color (converted to the specified color format) */
	uint16_t dst_color[6];
	uint32_t inc_base;

	/* translate to bit depth */
	switch (color_depth) {
	case COLOR_DEPTH_666:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_6;
	break;
	case COLOR_DEPTH_888:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_8;
	break;
	case COLOR_DEPTH_101010:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_10;
	break;
	case COLOR_DEPTH_121212:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_12;
	break;
	default:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_8;
	break;
	}

	switch (test_pattern) {
	case CONTROLLER_DP_TEST_PATTERN_COLORSQUARES:
	case CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA:
	{
		dyn_range = (test_pattern ==
				CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA ?
				TEST_PATTERN_DYN_RANGE_CEA :
				TEST_PATTERN_DYN_RANGE_VESA);
		mode = TEST_PATTERN_MODE_COLORSQUARES_RGB;

		CRTC_REG_UPDATE_2(CRTC0_CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_VRES, 6,
				CRTC_TEST_PATTERN_HRES, 6);

		CRTC_REG_UPDATE_4(CRTC0_CRTC_TEST_PATTERN_CONTROL,
				CRTC_TEST_PATTERN_EN, 1,
				CRTC_TEST_PATTERN_MODE, mode,
				CRTC_TEST_PATTERN_DYNAMIC_RANGE, dyn_range,
				CRTC_TEST_PATTERN_COLOR_FORMAT, bit_depth);
	}
	break;

	case CONTROLLER_DP_TEST_PATTERN_VERTICALBARS:
	case CONTROLLER_DP_TEST_PATTERN_HORIZONTALBARS:
	{
		mode = (test_pattern ==
			CONTROLLER_DP_TEST_PATTERN_VERTICALBARS ?
			TEST_PATTERN_MODE_VERTICALBARS :
			TEST_PATTERN_MODE_HORIZONTALBARS);

		switch (bit_depth) {
		case TEST_PATTERN_COLOR_FORMAT_BPC_6:
			dst_bpc = 6;
		break;
		case TEST_PATTERN_COLOR_FORMAT_BPC_8:
			dst_bpc = 8;
		break;
		case TEST_PATTERN_COLOR_FORMAT_BPC_10:
			dst_bpc = 10;
		break;
		default:
			dst_bpc = 8;
		break;
		}

		/* adjust color to the required colorFormat */
		for (index = 0; index < 6; index++) {
			/* dst = 2^dstBpc * src / 2^srcBpc = src >>
			 * (srcBpc - dstBpc);
			 */
			dst_color[index] =
				src_color[index] >> (src_bpc - dst_bpc);
		/* CRTC_TEST_PATTERN_DATA has 16 bits,
		 * lowest 6 are hardwired to ZERO
		 * color bits should be left aligned aligned to MSB
		 * XXXXXXXXXX000000 for 10 bit,
		 * XXXXXXXX00000000 for 8 bit and XXXXXX0000000000 for 6
		 */
			dst_color[index] <<= (16 - dst_bpc);
		}

		dm_write_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_PARAMETERS, tg110->offsets.crtc, 0);

		/* We have to write the mask before data, similar to pipeline.
		 * For example, for 8 bpc, if we want RGB0 to be magenta,
		 * and RGB1 to be cyan,
		 * we need to make 7 writes:
		 * MASK   DATA
		 * 000001 00000000 00000000                     set mask to R0
		 * 000010 11111111 00000000     R0 255, 0xFF00, set mask to G0
		 * 000100 00000000 00000000     G0 0,   0x0000, set mask to B0
		 * 001000 11111111 00000000     B0 255, 0xFF00, set mask to R1
		 * 010000 00000000 00000000     R1 0,   0x0000, set mask to G1
		 * 100000 11111111 00000000     G1 255, 0xFF00, set mask to B1
		 * 100000 11111111 00000000     B1 255, 0xFF00
		 *
		 * we will make a loop of 6 in which we prepare the mask,
		 * then write, then prepare the color for next write.
		 * first iteration will write mask only,
		 * but each next iteration color prepared in
		 * previous iteration will be written within new mask,
		 * the last component will written separately,
		 * mask is not changing between 6th and 7th write
		 * and color will be prepared by last iteration
		 */

		/* write color, color values mask in CRTC_TEST_PATTERN_MASK
		 * is B1, G1, R1, B0, G0, R0
		 */
		value = 0;
		for (index = 0; index < 6; index++) {
			/* prepare color mask, first write PATTERN_DATA
			 * will have all zeros
			 */
			set_reg_field_value(
				value,
				(1 << index),
				CRTC0_CRTC_TEST_PATTERN_COLOR,
				CRTC_TEST_PATTERN_MASK);
			/* write color component */
			dm_write_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_COLOR, tg110->offsets.crtc, value);
			/* prepare next color component,
			 * will be written in the next iteration
			 */
			set_reg_field_value(
				value,
				dst_color[index],
				CRTC0_CRTC_TEST_PATTERN_COLOR,
				CRTC_TEST_PATTERN_DATA);
		}
		/* write last color component,
		 * it's been already prepared in the loop
		 */
		dm_write_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_COLOR, tg110->offsets.crtc, value);

		/* enable test pattern */
		CRTC_REG_UPDATE_4(CRTC0_CRTC_TEST_PATTERN_CONTROL,
				CRTC_TEST_PATTERN_EN, 1,
				CRTC_TEST_PATTERN_MODE, mode,
				CRTC_TEST_PATTERN_DYNAMIC_RANGE, 0,
				CRTC_TEST_PATTERN_COLOR_FORMAT, bit_depth);
	}
	break;

	case CONTROLLER_DP_TEST_PATTERN_COLORRAMP:
	{
		mode = (bit_depth ==
			TEST_PATTERN_COLOR_FORMAT_BPC_10 ?
			TEST_PATTERN_MODE_DUALRAMP_RGB :
			TEST_PATTERN_MODE_SINGLERAMP_RGB);

		switch (bit_depth) {
		case TEST_PATTERN_COLOR_FORMAT_BPC_6:
			dst_bpc = 6;
		break;
		case TEST_PATTERN_COLOR_FORMAT_BPC_8:
			dst_bpc = 8;
		break;
		case TEST_PATTERN_COLOR_FORMAT_BPC_10:
			dst_bpc = 10;
		break;
		default:
			dst_bpc = 8;
		break;
		}

		/* increment for the first ramp for one color gradation
		 * 1 gradation for 6-bit color is 2^10
		 * gradations in 16-bit color
		 */
		inc_base = (src_bpc - dst_bpc);

		switch (bit_depth) {
		case TEST_PATTERN_COLOR_FORMAT_BPC_6:
		{
			CRTC_REG_UPDATE_5(CRTC0_CRTC_TEST_PATTERN_PARAMETERS,
					CRTC_TEST_PATTERN_INC0, inc_base,
					CRTC_TEST_PATTERN_INC1, 0,
					CRTC_TEST_PATTERN_HRES, 6,
					CRTC_TEST_PATTERN_VRES, 6,
					CRTC_TEST_PATTERN_RAMP0_OFFSET, 0);
		}
		break;
		case TEST_PATTERN_COLOR_FORMAT_BPC_8:
		{
			CRTC_REG_UPDATE_5(CRTC0_CRTC_TEST_PATTERN_PARAMETERS,
					CRTC_TEST_PATTERN_INC0, inc_base,
					CRTC_TEST_PATTERN_INC1, 0,
					CRTC_TEST_PATTERN_HRES, 8,
					CRTC_TEST_PATTERN_VRES, 6,
					CRTC_TEST_PATTERN_RAMP0_OFFSET, 0);
		}
		break;
		case TEST_PATTERN_COLOR_FORMAT_BPC_10:
		{
			CRTC_REG_UPDATE_5(CRTC0_CRTC_TEST_PATTERN_PARAMETERS,
					CRTC_TEST_PATTERN_INC0, inc_base,
					CRTC_TEST_PATTERN_INC1, inc_base + 2,
					CRTC_TEST_PATTERN_HRES, 8,
					CRTC_TEST_PATTERN_VRES, 5,
					CRTC_TEST_PATTERN_RAMP0_OFFSET, 384 << 6);
		}
		break;
		default:
		break;
		}

		dm_write_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_COLOR, tg110->offsets.crtc, 0);

		/* enable test pattern */
		dm_write_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_CONTROL, tg110->offsets.crtc, 0);

		CRTC_REG_UPDATE_4(CRTC0_CRTC_TEST_PATTERN_CONTROL,
				CRTC_TEST_PATTERN_EN, 1,
				CRTC_TEST_PATTERN_MODE, mode,
				CRTC_TEST_PATTERN_DYNAMIC_RANGE, 0,
				CRTC_TEST_PATTERN_COLOR_FORMAT, bit_depth);
	}
	break;
	case CONTROLLER_DP_TEST_PATTERN_VIDEOMODE:
	{
		value = 0;
		dm_write_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_CONTROL, tg110->offsets.crtc,  value);
		dm_write_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_COLOR, tg110->offsets.crtc, value);
		dm_write_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_PARAMETERS, tg110->offsets.crtc, value);
	}
	break;
	default:
	break;
	}
}