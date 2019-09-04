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
typedef  enum mi_tiling_format { ____Placeholder_mi_tiling_format } mi_tiling_format ;

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
 int mi_tiling_1D ; 
 int mi_tiling_2D ; 
 int mi_tiling_linear ; 

__attribute__((used)) static enum mi_tiling_format get_mi_tiling(
		union dc_tiling_info *tiling_info)
{
	switch (tiling_info->gfx8.array_mode) {
	case DC_ARRAY_1D_TILED_THIN1:
	case DC_ARRAY_1D_TILED_THICK:
	case DC_ARRAY_PRT_TILED_THIN1:
		return mi_tiling_1D;
	case DC_ARRAY_2D_TILED_THIN1:
	case DC_ARRAY_2D_TILED_THICK:
	case DC_ARRAY_2D_TILED_X_THICK:
	case DC_ARRAY_PRT_2D_TILED_THIN1:
	case DC_ARRAY_PRT_2D_TILED_THICK:
		return mi_tiling_2D;
	case DC_ARRAY_LINEAR_GENERAL:
	case DC_ARRAY_LINEAR_ALLIGNED:
		return mi_tiling_linear;
	default:
		return mi_tiling_2D;
	}
}