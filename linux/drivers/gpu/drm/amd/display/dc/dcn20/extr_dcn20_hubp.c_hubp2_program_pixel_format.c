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
struct hubp {int dummy; } ;
struct dcn20_hubp {int dummy; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  CROSSBAR_SRC_CB_B ; 
 int /*<<< orphan*/  CROSSBAR_SRC_CR_R ; 
 int /*<<< orphan*/  DCSURF_SURFACE_CONFIG ; 
 int /*<<< orphan*/  HUBPRET_CONTROL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT ; 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 147 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 146 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS 145 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 144 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB1555 143 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 142 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F 141 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 140 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 139 
#define  SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FIX 138 
#define  SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FLOAT 137 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FIX 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FLOAT 135 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 134 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr 133 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb 132 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr 131 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb 130 
#define  SURFACE_PIXEL_FORMAT_VIDEO_ACrYCb2101010 129 
#define  SURFACE_PIXEL_FORMAT_VIDEO_AYCrCb8888 128 
 struct dcn20_hubp* TO_DCN20_HUBP (struct hubp*) ; 

void hubp2_program_pixel_format(
	struct hubp *hubp,
	enum surface_pixel_format format)
{
	struct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t red_bar = 3;
	uint32_t blue_bar = 2;

	/* swap for ABGR format */
	if (format == SURFACE_PIXEL_FORMAT_GRPH_ABGR8888
			|| format == SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010
			|| format == SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS
			|| format == SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F) {
		red_bar = 2;
		blue_bar = 3;
	}

	REG_UPDATE_2(HUBPRET_CONTROL,
			CROSSBAR_SRC_CB_B, blue_bar,
			CROSSBAR_SRC_CR_R, red_bar);

	/* Mapping is same as ipp programming (cnvc) */

	switch (format)	{
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 1);
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 3);
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 8);
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 10);
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 22);
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:/*we use crossbar already*/
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 24);
		break;

	case SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 65);
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 64);
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 67);
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 66);
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_AYCrCb8888:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 12);
		break;
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	case SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FIX:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 112);
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FIX:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 113);
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_ACrYCb2101010:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 114);
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FLOAT:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 118);
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FLOAT:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 119);
		break;
#endif
	default:
		BREAK_TO_DEBUGGER();
		break;
	}

	/* don't see the need of program the xbar in DCN 1.0 */
}