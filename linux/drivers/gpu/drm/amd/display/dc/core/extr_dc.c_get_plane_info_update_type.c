#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int color_space_change; int horizontal_mirror_change; int rotation_change; int pixel_format_change; int stereo_format_change; int per_pixel_alpha_change; int global_alpha_change; int sdr_white_level; int dcc_change; int bpp_change; int plane_size_change; int swizzle_change; int bandwidth_change; } ;
union surface_update_flags {TYPE_8__ bits; } ;
typedef  union dc_tiling_info {int dummy; } dc_tiling_info ;
struct dc_surface_update {TYPE_7__* plane_info; TYPE_5__* surface; } ;
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;
struct TYPE_15__ {scalar_t__ swizzle; } ;
struct TYPE_18__ {TYPE_6__ gfx9; } ;
struct TYPE_12__ {scalar_t__ surface_pitch; scalar_t__ chroma_pitch; } ;
struct TYPE_10__ {scalar_t__ enable; scalar_t__ independent_64b_blks; scalar_t__ meta_pitch; } ;
struct TYPE_16__ {scalar_t__ color_space; scalar_t__ horizontal_mirror; scalar_t__ rotation; scalar_t__ format; scalar_t__ stereo_format; scalar_t__ per_pixel_alpha; scalar_t__ global_alpha_value; scalar_t__ sdr_white_level; TYPE_9__ tiling_info; TYPE_3__ plane_size; TYPE_1__ dcc; } ;
struct TYPE_13__ {scalar_t__ surface_pitch; scalar_t__ chroma_pitch; } ;
struct TYPE_11__ {scalar_t__ enable; scalar_t__ independent_64b_blks; scalar_t__ meta_pitch; } ;
struct TYPE_14__ {scalar_t__ color_space; scalar_t__ horizontal_mirror; scalar_t__ rotation; scalar_t__ format; scalar_t__ stereo_format; scalar_t__ per_pixel_alpha; scalar_t__ global_alpha_value; scalar_t__ sdr_white_level; int /*<<< orphan*/  tiling_info; TYPE_4__ plane_size; TYPE_2__ dcc; union surface_update_flags update_flags; } ;

/* Variables and functions */
 scalar_t__ DC_SW_LINEAR ; 
 int UPDATE_TYPE_FAST ; 
 int /*<<< orphan*/  UPDATE_TYPE_FULL ; 
 int /*<<< orphan*/  UPDATE_TYPE_MED ; 
 int /*<<< orphan*/  elevate_update_type (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (TYPE_9__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ resource_pixel_format_to_bpp (scalar_t__) ; 

__attribute__((used)) static enum surface_update_type get_plane_info_update_type(const struct dc_surface_update *u)
{
	union surface_update_flags *update_flags = &u->surface->update_flags;
	enum surface_update_type update_type = UPDATE_TYPE_FAST;

	if (!u->plane_info)
		return UPDATE_TYPE_FAST;

	if (u->plane_info->color_space != u->surface->color_space) {
		update_flags->bits.color_space_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (u->plane_info->horizontal_mirror != u->surface->horizontal_mirror) {
		update_flags->bits.horizontal_mirror_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (u->plane_info->rotation != u->surface->rotation) {
		update_flags->bits.rotation_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_FULL);
	}

	if (u->plane_info->format != u->surface->format) {
		update_flags->bits.pixel_format_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_FULL);
	}

	if (u->plane_info->stereo_format != u->surface->stereo_format) {
		update_flags->bits.stereo_format_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_FULL);
	}

	if (u->plane_info->per_pixel_alpha != u->surface->per_pixel_alpha) {
		update_flags->bits.per_pixel_alpha_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (u->plane_info->global_alpha_value != u->surface->global_alpha_value) {
		update_flags->bits.global_alpha_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (u->plane_info->sdr_white_level != u->surface->sdr_white_level) {
		update_flags->bits.sdr_white_level = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (u->plane_info->dcc.enable != u->surface->dcc.enable
			|| u->plane_info->dcc.independent_64b_blks != u->surface->dcc.independent_64b_blks
			|| u->plane_info->dcc.meta_pitch != u->surface->dcc.meta_pitch) {
		update_flags->bits.dcc_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	}

	if (resource_pixel_format_to_bpp(u->plane_info->format) !=
			resource_pixel_format_to_bpp(u->surface->format)) {
		/* different bytes per element will require full bandwidth
		 * and DML calculation
		 */
		update_flags->bits.bpp_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_FULL);
	}

	if (u->plane_info->plane_size.surface_pitch != u->surface->plane_size.surface_pitch
			|| u->plane_info->plane_size.surface_pitch != u->surface->plane_size.surface_pitch
			|| u->plane_info->plane_size.chroma_pitch != u->surface->plane_size.chroma_pitch) {
		update_flags->bits.plane_size_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	}


	if (memcmp(&u->plane_info->tiling_info, &u->surface->tiling_info,
			sizeof(union dc_tiling_info)) != 0) {
		update_flags->bits.swizzle_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);

		/* todo: below are HW dependent, we should add a hook to
		 * DCE/N resource and validated there.
		 */
		if (u->plane_info->tiling_info.gfx9.swizzle != DC_SW_LINEAR) {
			/* swizzled mode requires RQ to be setup properly,
			 * thus need to run DML to calculate RQ settings
			 */
			update_flags->bits.bandwidth_change = 1;
			elevate_update_type(&update_type, UPDATE_TYPE_FULL);
		}
	}

	/* This should be UPDATE_TYPE_FAST if nothing has changed. */
	return update_type;
}