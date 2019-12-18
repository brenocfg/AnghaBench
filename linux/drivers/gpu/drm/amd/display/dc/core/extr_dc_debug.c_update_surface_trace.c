#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct dc_surface_update {TYPE_17__* scaling_info; TYPE_12__* plane_info; TYPE_6__* flip_addr; } ;
struct dc {TYPE_1__* ctx; } ;
struct TYPE_34__ {int /*<<< orphan*/  array_mode; int /*<<< orphan*/  pipe_config; int /*<<< orphan*/  tile_mode_c; int /*<<< orphan*/  tile_mode; int /*<<< orphan*/  tile_split_c; int /*<<< orphan*/  tile_split; int /*<<< orphan*/  tile_aspect_c; int /*<<< orphan*/  tile_aspect; int /*<<< orphan*/  bank_height_c; int /*<<< orphan*/  bank_height; int /*<<< orphan*/  bank_width_c; int /*<<< orphan*/  bank_width; int /*<<< orphan*/  num_banks; } ;
struct TYPE_32__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_33__ {TYPE_7__ surface_size; int /*<<< orphan*/  surface_pitch; } ;
struct TYPE_28__ {int /*<<< orphan*/  quad_part; } ;
struct TYPE_27__ {int /*<<< orphan*/  quad_part; } ;
struct TYPE_29__ {TYPE_3__ meta_addr; TYPE_2__ addr; } ;
struct TYPE_30__ {TYPE_4__ grph; int /*<<< orphan*/  type; } ;
struct TYPE_31__ {int /*<<< orphan*/  flip_immediate; TYPE_5__ address; } ;
struct TYPE_26__ {int /*<<< orphan*/  logger; } ;
struct TYPE_24__ {int /*<<< orphan*/  v_taps_c; int /*<<< orphan*/  h_taps_c; int /*<<< orphan*/  v_taps; int /*<<< orphan*/  h_taps; } ;
struct TYPE_23__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_22__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_21__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_25__ {TYPE_16__ scaling_quality; TYPE_15__ clip_rect; TYPE_14__ dst_rect; TYPE_13__ src_rect; } ;
struct TYPE_18__ {int /*<<< orphan*/  swizzle; } ;
struct TYPE_19__ {TYPE_10__ gfx9; TYPE_9__ gfx8; } ;
struct TYPE_20__ {TYPE_11__ tiling_info; int /*<<< orphan*/  per_pixel_alpha; int /*<<< orphan*/  visible; int /*<<< orphan*/  stereo_format; int /*<<< orphan*/  rotation; TYPE_8__ plane_size; int /*<<< orphan*/  format; int /*<<< orphan*/  color_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SURFACE_TRACE (char*,...) ; 

void update_surface_trace(
		struct dc *dc,
		const struct dc_surface_update *updates,
		int surface_count)
{
	int i;
	DC_LOGGER_INIT(dc->ctx->logger);

	for (i = 0; i < surface_count; i++) {
		const struct dc_surface_update *update = &updates[i];

		SURFACE_TRACE("Update %d\n", i);
		if (update->flip_addr) {
			SURFACE_TRACE("flip_addr->address.type = %d;\n"
					"flip_addr->address.grph.addr.quad_part = 0x%llX;\n"
					"flip_addr->address.grph.meta_addr.quad_part = 0x%llX;\n"
					"flip_addr->flip_immediate = %d;\n",
					update->flip_addr->address.type,
					update->flip_addr->address.grph.addr.quad_part,
					update->flip_addr->address.grph.meta_addr.quad_part,
					update->flip_addr->flip_immediate);
		}

		if (update->plane_info) {
			SURFACE_TRACE(
					"plane_info->color_space = %d;\n"
					"plane_info->format = %d;\n"
					"plane_info->plane_size.surface_pitch = %d;\n"
					"plane_info->plane_size.surface_size.height = %d;\n"
					"plane_info->plane_size.surface_size.width = %d;\n"
					"plane_info->plane_size.surface_size.x = %d;\n"
					"plane_info->plane_size.surface_size.y = %d;\n"
					"plane_info->rotation = %d;\n"
					"plane_info->stereo_format = %d;\n",
					update->plane_info->color_space,
					update->plane_info->format,
					update->plane_info->plane_size.surface_pitch,
					update->plane_info->plane_size.surface_size.height,
					update->plane_info->plane_size.surface_size.width,
					update->plane_info->plane_size.surface_size.x,
					update->plane_info->plane_size.surface_size.y,
					update->plane_info->rotation,
					update->plane_info->stereo_format);

			SURFACE_TRACE(
					"plane_info->tiling_info.gfx8.num_banks = %d;\n"
					"plane_info->tiling_info.gfx8.bank_width = %d;\n"
					"plane_info->tiling_info.gfx8.bank_width_c = %d;\n"
					"plane_info->tiling_info.gfx8.bank_height = %d;\n"
					"plane_info->tiling_info.gfx8.bank_height_c = %d;\n"
					"plane_info->tiling_info.gfx8.tile_aspect = %d;\n"
					"plane_info->tiling_info.gfx8.tile_aspect_c = %d;\n"
					"plane_info->tiling_info.gfx8.tile_split = %d;\n"
					"plane_info->tiling_info.gfx8.tile_split_c = %d;\n"
					"plane_info->tiling_info.gfx8.tile_mode = %d;\n"
					"plane_info->tiling_info.gfx8.tile_mode_c = %d;\n",
					update->plane_info->tiling_info.gfx8.num_banks,
					update->plane_info->tiling_info.gfx8.bank_width,
					update->plane_info->tiling_info.gfx8.bank_width_c,
					update->plane_info->tiling_info.gfx8.bank_height,
					update->plane_info->tiling_info.gfx8.bank_height_c,
					update->plane_info->tiling_info.gfx8.tile_aspect,
					update->plane_info->tiling_info.gfx8.tile_aspect_c,
					update->plane_info->tiling_info.gfx8.tile_split,
					update->plane_info->tiling_info.gfx8.tile_split_c,
					update->plane_info->tiling_info.gfx8.tile_mode,
					update->plane_info->tiling_info.gfx8.tile_mode_c);

			SURFACE_TRACE(
					"plane_info->tiling_info.gfx8.pipe_config = %d;\n"
					"plane_info->tiling_info.gfx8.array_mode = %d;\n"
					"plane_info->visible = %d;\n"
					"plane_info->per_pixel_alpha = %d;\n",
					update->plane_info->tiling_info.gfx8.pipe_config,
					update->plane_info->tiling_info.gfx8.array_mode,
					update->plane_info->visible,
					update->plane_info->per_pixel_alpha);

			SURFACE_TRACE("surface->tiling_info.gfx9.swizzle = %d;\n",
					update->plane_info->tiling_info.gfx9.swizzle);
		}

		if (update->scaling_info) {
			SURFACE_TRACE(
					"scaling_info->src_rect.x = %d;\n"
					"scaling_info->src_rect.y = %d;\n"
					"scaling_info->src_rect.width = %d;\n"
					"scaling_info->src_rect.height = %d;\n"
					"scaling_info->dst_rect.x = %d;\n"
					"scaling_info->dst_rect.y = %d;\n"
					"scaling_info->dst_rect.width = %d;\n"
					"scaling_info->dst_rect.height = %d;\n"
					"scaling_info->clip_rect.x = %d;\n"
					"scaling_info->clip_rect.y = %d;\n"
					"scaling_info->clip_rect.width = %d;\n"
					"scaling_info->clip_rect.height = %d;\n"
					"scaling_info->scaling_quality.h_taps = %d;\n"
					"scaling_info->scaling_quality.v_taps = %d;\n"
					"scaling_info->scaling_quality.h_taps_c = %d;\n"
					"scaling_info->scaling_quality.v_taps_c = %d;\n",
					update->scaling_info->src_rect.x,
					update->scaling_info->src_rect.y,
					update->scaling_info->src_rect.width,
					update->scaling_info->src_rect.height,
					update->scaling_info->dst_rect.x,
					update->scaling_info->dst_rect.y,
					update->scaling_info->dst_rect.width,
					update->scaling_info->dst_rect.height,
					update->scaling_info->clip_rect.x,
					update->scaling_info->clip_rect.y,
					update->scaling_info->clip_rect.width,
					update->scaling_info->clip_rect.height,
					update->scaling_info->scaling_quality.h_taps,
					update->scaling_info->scaling_quality.v_taps,
					update->scaling_info->scaling_quality.h_taps_c,
					update->scaling_info->scaling_quality.v_taps_c);
		}
		SURFACE_TRACE("\n");
	}
	SURFACE_TRACE("\n");
}