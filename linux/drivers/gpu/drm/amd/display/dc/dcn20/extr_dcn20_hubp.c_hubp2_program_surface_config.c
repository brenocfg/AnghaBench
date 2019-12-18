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
typedef  union dc_tiling_info {int dummy; } dc_tiling_info ;
struct plane_size {int dummy; } ;
struct hubp {int dummy; } ;
struct dcn20_hubp {int dummy; } ;
struct dc_plane_dcc_param {int /*<<< orphan*/  independent_64b_blks; int /*<<< orphan*/  enable; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;
typedef  enum dc_rotation_angle { ____Placeholder_dc_rotation_angle } dc_rotation_angle ;

/* Variables and functions */
 struct dcn20_hubp* TO_DCN20_HUBP (struct hubp*) ; 
 int /*<<< orphan*/  hubp2_dcc_control (struct hubp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hubp2_program_pixel_format (struct hubp*,int) ; 
 int /*<<< orphan*/  hubp2_program_rotation (struct hubp*,int,int) ; 
 int /*<<< orphan*/  hubp2_program_size (struct hubp*,int,struct plane_size*,struct dc_plane_dcc_param*) ; 
 int /*<<< orphan*/  hubp2_program_tiling (struct dcn20_hubp*,union dc_tiling_info*,int) ; 

void hubp2_program_surface_config(
	struct hubp *hubp,
	enum surface_pixel_format format,
	union dc_tiling_info *tiling_info,
	struct plane_size *plane_size,
	enum dc_rotation_angle rotation,
	struct dc_plane_dcc_param *dcc,
	bool horizontal_mirror,
	unsigned int compat_level)
{
	struct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	hubp2_dcc_control(hubp, dcc->enable, dcc->independent_64b_blks);
	hubp2_program_tiling(hubp2, tiling_info, format);
	hubp2_program_size(hubp, format, plane_size, dcc);
	hubp2_program_rotation(hubp, rotation, horizontal_mirror);
	hubp2_program_pixel_format(hubp, format);
}