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
typedef  int uint16_t ;
struct tg_color {int dummy; } ;
struct output_pixel_processor {int dummy; } ;
struct dcn20_opp {int dummy; } ;
typedef  enum test_pattern_mode { ____Placeholder_test_pattern_mode } test_pattern_mode ;
typedef  enum test_pattern_dyn_range { ____Placeholder_test_pattern_dyn_range } test_pattern_dyn_range ;
typedef  enum test_pattern_color_format { ____Placeholder_test_pattern_color_format } test_pattern_color_format ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;
typedef  enum controller_dp_test_pattern { ____Placeholder_controller_dp_test_pattern } controller_dp_test_pattern ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 141 
#define  COLOR_DEPTH_121212 140 
#define  COLOR_DEPTH_666 139 
#define  COLOR_DEPTH_888 138 
#define  CONTROLLER_DP_TEST_PATTERN_COLORRAMP 137 
#define  CONTROLLER_DP_TEST_PATTERN_COLORSQUARES 136 
#define  CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA 135 
#define  CONTROLLER_DP_TEST_PATTERN_HORIZONTALBARS 134 
#define  CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR 133 
#define  CONTROLLER_DP_TEST_PATTERN_VERTICALBARS 132 
#define  CONTROLLER_DP_TEST_PATTERN_VIDEOMODE 131 
 int /*<<< orphan*/  DPG_ACTIVE_HEIGHT ; 
 int /*<<< orphan*/  DPG_ACTIVE_WIDTH ; 
 int /*<<< orphan*/  DPG_BIT_DEPTH ; 
 int /*<<< orphan*/  DPG_COLOUR0_B_CB ; 
 int /*<<< orphan*/  DPG_COLOUR0_G_Y ; 
 int /*<<< orphan*/  DPG_COLOUR0_R_CR ; 
 int /*<<< orphan*/  DPG_COLOUR1_B_CB ; 
 int /*<<< orphan*/  DPG_COLOUR1_G_Y ; 
 int /*<<< orphan*/  DPG_COLOUR1_R_CR ; 
 int /*<<< orphan*/  DPG_COLOUR_B_CB ; 
 int /*<<< orphan*/  DPG_COLOUR_G_Y ; 
 int /*<<< orphan*/  DPG_COLOUR_R_CR ; 
 int /*<<< orphan*/  DPG_CONTROL ; 
 int /*<<< orphan*/  DPG_DIMENSIONS ; 
 int /*<<< orphan*/  DPG_DYNAMIC_RANGE ; 
 int /*<<< orphan*/  DPG_EN ; 
 int /*<<< orphan*/  DPG_HRES ; 
 int /*<<< orphan*/  DPG_INC0 ; 
 int /*<<< orphan*/  DPG_INC1 ; 
 int /*<<< orphan*/  DPG_MODE ; 
 int /*<<< orphan*/  DPG_RAMP0_OFFSET ; 
 int /*<<< orphan*/  DPG_RAMP_CONTROL ; 
 int /*<<< orphan*/  DPG_VRES ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 struct dcn20_opp* TO_DCN20_OPP (struct output_pixel_processor*) ; 
 int /*<<< orphan*/  opp2_dpg_set_blank_color (struct output_pixel_processor*,struct tg_color const*) ; 

void opp2_set_disp_pattern_generator(
		struct output_pixel_processor *opp,
		enum controller_dp_test_pattern test_pattern,
		enum dc_color_depth color_depth,
		const struct tg_color *solid_color,
		int width,
		int height)
{
	struct dcn20_opp *oppn20 = TO_DCN20_OPP(opp);
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

	/* set DPG dimentions */
	REG_SET_2(DPG_DIMENSIONS, 0,
		DPG_ACTIVE_WIDTH, width,
		DPG_ACTIVE_HEIGHT, height);

	switch (test_pattern) {
	case CONTROLLER_DP_TEST_PATTERN_COLORSQUARES:
	case CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA:
	{
		dyn_range = (test_pattern ==
				CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA ?
				TEST_PATTERN_DYN_RANGE_CEA :
				TEST_PATTERN_DYN_RANGE_VESA);

		REG_UPDATE_6(DPG_CONTROL,
			DPG_EN, 1,
			DPG_MODE, TEST_PATTERN_MODE_COLORSQUARES_RGB,
			DPG_DYNAMIC_RANGE, dyn_range,
			DPG_BIT_DEPTH, bit_depth,
			DPG_VRES, 6,
			DPG_HRES, 6);
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
		/* DPG_COLOUR registers are 16-bit MSB aligned value with bits 3:0 hardwired to ZERO.
		 * XXXXXXXXXX000000 for 10 bit,
		 * XXXXXXXX00000000 for 8 bit,
		 * XXXXXX0000000000 for 6 bits
		 */
			dst_color[index] <<= (16 - dst_bpc);
		}

		REG_SET_2(DPG_COLOUR_R_CR, 0,
				DPG_COLOUR1_R_CR, dst_color[0],
				DPG_COLOUR0_R_CR, dst_color[3]);
		REG_SET_2(DPG_COLOUR_G_Y, 0,
				DPG_COLOUR1_G_Y, dst_color[1],
				DPG_COLOUR0_G_Y, dst_color[4]);
		REG_SET_2(DPG_COLOUR_B_CB, 0,
				DPG_COLOUR1_B_CB, dst_color[2],
				DPG_COLOUR0_B_CB, dst_color[5]);

		/* enable test pattern */
		REG_UPDATE_6(DPG_CONTROL,
			DPG_EN, 1,
			DPG_MODE, mode,
			DPG_DYNAMIC_RANGE, 0,
			DPG_BIT_DEPTH, bit_depth,
			DPG_VRES, 0,
			DPG_HRES, 0);
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
			REG_SET_3(DPG_RAMP_CONTROL, 0,
				DPG_RAMP0_OFFSET, 0,
				DPG_INC0, inc_base,
				DPG_INC1, 0);
			REG_UPDATE_2(DPG_CONTROL,
				DPG_VRES, 6,
				DPG_HRES, 6);
		}
		break;
		case TEST_PATTERN_COLOR_FORMAT_BPC_8:
		{
			REG_SET_3(DPG_RAMP_CONTROL, 0,
				DPG_RAMP0_OFFSET, 0,
				DPG_INC0, inc_base,
				DPG_INC1, 0);
			REG_UPDATE_2(DPG_CONTROL,
				DPG_VRES, 6,
				DPG_HRES, 8);
		}
		break;
		case TEST_PATTERN_COLOR_FORMAT_BPC_10:
		{
			REG_SET_3(DPG_RAMP_CONTROL, 0,
				DPG_RAMP0_OFFSET, 384 << 6,
				DPG_INC0, inc_base,
				DPG_INC1, inc_base + 2);
			REG_UPDATE_2(DPG_CONTROL,
				DPG_VRES, 5,
				DPG_HRES, 8);
		}
		break;
		default:
		break;
		}

		/* enable test pattern */
		REG_UPDATE_4(DPG_CONTROL,
			DPG_EN, 1,
			DPG_MODE, mode,
			DPG_DYNAMIC_RANGE, 0,
			DPG_BIT_DEPTH, bit_depth);
	}
	break;
	case CONTROLLER_DP_TEST_PATTERN_VIDEOMODE:
	{
		REG_WRITE(DPG_CONTROL, 0);
		REG_WRITE(DPG_COLOUR_R_CR, 0);
		REG_WRITE(DPG_COLOUR_G_Y, 0);
		REG_WRITE(DPG_COLOUR_B_CB, 0);
		REG_WRITE(DPG_RAMP_CONTROL, 0);
	}
	break;
	case CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR:
	{
		opp2_dpg_set_blank_color(opp, solid_color);
		REG_UPDATE_2(DPG_CONTROL,
				DPG_EN, 1,
				DPG_MODE, TEST_PATTERN_MODE_HORIZONTALBARS);

		REG_SET_2(DPG_DIMENSIONS, 0,
				DPG_ACTIVE_WIDTH, width,
				DPG_ACTIVE_HEIGHT, height);
	}
	break;
	default:
		break;

	}
}