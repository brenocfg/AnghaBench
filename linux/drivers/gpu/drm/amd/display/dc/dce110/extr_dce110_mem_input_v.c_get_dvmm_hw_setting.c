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
struct TYPE_2__ {int array_mode; } ;
union dc_tiling_info {TYPE_1__ gfx8; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;

/* Variables and functions */
#define  DC_ARRAY_1D_TILED_THICK 137 
#define  DC_ARRAY_1D_TILED_THIN1 136 
#define  DC_ARRAY_2D_TILED_THICK 135 
#define  DC_ARRAY_2D_TILED_THIN1 134 
#define  DC_ARRAY_2D_TILED_X_THICK 133 
#define  DC_ARRAY_LINEAR_ALLIGNED 132 
#define  DC_ARRAY_LINEAR_GENERAL 131 
#define  DC_ARRAY_PRT_2D_TILED_THICK 130 
#define  DC_ARRAY_PRT_2D_TILED_THIN1 129 
#define  DC_ARRAY_PRT_TILED_THIN1 128 
 int SURFACE_PIXEL_FORMAT_INVALID ; 
 int SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 
 unsigned int const** dvmm_Hw_Setting_1DTiling ; 
 unsigned int const** dvmm_Hw_Setting_2DTiling ; 
 unsigned int const** dvmm_Hw_Setting_Linear ; 

__attribute__((used)) static const unsigned int *get_dvmm_hw_setting(
		union dc_tiling_info *tiling_info,
		enum surface_pixel_format format,
		bool chroma)
{
	enum bits_per_pixel {
		bpp_8 = 0,
		bpp_16,
		bpp_32,
		bpp_64
	} bpp;

	if (format >= SURFACE_PIXEL_FORMAT_INVALID)
		bpp = bpp_32;
	else if (format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		bpp = chroma ? bpp_16 : bpp_8;
	else
		bpp = bpp_8;

	switch (tiling_info->gfx8.array_mode) {
	case DC_ARRAY_1D_TILED_THIN1:
	case DC_ARRAY_1D_TILED_THICK:
	case DC_ARRAY_PRT_TILED_THIN1:
		return dvmm_Hw_Setting_1DTiling[bpp];
	case DC_ARRAY_2D_TILED_THIN1:
	case DC_ARRAY_2D_TILED_THICK:
	case DC_ARRAY_2D_TILED_X_THICK:
	case DC_ARRAY_PRT_2D_TILED_THIN1:
	case DC_ARRAY_PRT_2D_TILED_THICK:
		return dvmm_Hw_Setting_2DTiling[bpp];
	case DC_ARRAY_LINEAR_GENERAL:
	case DC_ARRAY_LINEAR_ALLIGNED:
		return dvmm_Hw_Setting_Linear[bpp];
	default:
		return dvmm_Hw_Setting_2DTiling[bpp];
	}
}