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
struct dce_mem_input {int dummy; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERR (char*) ; 
 int /*<<< orphan*/  GRPH_BLUE_CROSSBAR ; 
 int /*<<< orphan*/  GRPH_CONTROL ; 
 int /*<<< orphan*/  GRPH_DEPTH ; 
 int /*<<< orphan*/  GRPH_FORMAT ; 
 int /*<<< orphan*/  GRPH_PRESCALE_B_SIGN ; 
 int /*<<< orphan*/  GRPH_PRESCALE_G_SIGN ; 
 int /*<<< orphan*/  GRPH_PRESCALE_R_SIGN ; 
 int /*<<< orphan*/  GRPH_PRESCALE_SELECT ; 
 int /*<<< orphan*/  GRPH_RED_CROSSBAR ; 
 int /*<<< orphan*/  GRPH_SWAP_CNTL ; 
 int /*<<< orphan*/  PRESCALE_GRPH_CONTROL ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 138 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 137 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 135 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB1555 134 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 133 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F 132 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 131 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 130 
#define  SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS 129 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 128 

__attribute__((used)) static void program_grph_pixel_format(
	struct dce_mem_input *dce_mi,
	enum surface_pixel_format format)
{
	uint32_t red_xbar = 0, blue_xbar = 0; /* no swap */
	uint32_t grph_depth = 0, grph_format = 0;
	uint32_t sign = 0, floating = 0;

	if (format == SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 ||
			/*todo: doesn't look like we handle BGRA here,
			 *  should problem swap endian*/
		format == SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 ||
		format == SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS ||
		format == SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F) {
		/* ABGR formats */
		red_xbar = 2;
		blue_xbar = 2;
	}

	REG_SET_2(GRPH_SWAP_CNTL, 0,
			GRPH_RED_CROSSBAR, red_xbar,
			GRPH_BLUE_CROSSBAR, blue_xbar);

	switch (format) {
	case SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS:
		grph_depth = 0;
		grph_format = 0;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		grph_depth = 1;
		grph_format = 0;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		grph_depth = 1;
		grph_format = 1;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		grph_depth = 2;
		grph_format = 0;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		grph_depth = 2;
		grph_format = 1;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		sign = 1;
		floating = 1;
		/* fall through */
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F: /* shouldn't this get float too? */
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		grph_depth = 3;
		grph_format = 0;
		break;
	default:
		DC_ERR("unsupported grph pixel format");
		break;
	}

	REG_UPDATE_2(GRPH_CONTROL,
			GRPH_DEPTH, grph_depth,
			GRPH_FORMAT, grph_format);

	REG_UPDATE_4(PRESCALE_GRPH_CONTROL,
			GRPH_PRESCALE_SELECT, floating,
			GRPH_PRESCALE_R_SIGN, sign,
			GRPH_PRESCALE_G_SIGN, sign,
			GRPH_PRESCALE_B_SIGN, sign);
}