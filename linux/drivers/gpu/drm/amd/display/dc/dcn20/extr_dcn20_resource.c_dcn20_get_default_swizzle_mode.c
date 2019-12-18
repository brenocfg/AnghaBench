#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int swizzle; } ;
struct TYPE_4__ {TYPE_1__ gfx9; } ;
struct dc_plane_state {int format; TYPE_2__ tiling_info; } ;
typedef  enum swizzle_mode_values { ____Placeholder_swizzle_mode_values } swizzle_mode_values ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;

/* Variables and functions */
 int DC_OK ; 
 int DC_SW_64KB_D ; 
 int DC_SW_64KB_S ; 
 int DC_SW_LINEAR ; 
 unsigned int resource_pixel_format_to_bpp (int) ; 

enum dc_status dcn20_get_default_swizzle_mode(struct dc_plane_state *plane_state)
{
	enum dc_status result = DC_OK;

	enum surface_pixel_format surf_pix_format = plane_state->format;
	unsigned int bpp = resource_pixel_format_to_bpp(surf_pix_format);

	enum swizzle_mode_values swizzle = DC_SW_LINEAR;

	if (bpp == 64)
		swizzle = DC_SW_64KB_D;
	else
		swizzle = DC_SW_64KB_S;

	plane_state->tiling_info.gfx9.swizzle = swizzle;
	return result;
}