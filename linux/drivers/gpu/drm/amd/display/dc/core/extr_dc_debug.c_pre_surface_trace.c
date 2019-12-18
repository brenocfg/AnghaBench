#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  swizzle; } ;
struct TYPE_18__ {int /*<<< orphan*/  array_mode; int /*<<< orphan*/  pipe_config; int /*<<< orphan*/  tile_mode_c; int /*<<< orphan*/  tile_mode; int /*<<< orphan*/  tile_split_c; int /*<<< orphan*/  tile_split; int /*<<< orphan*/  tile_aspect_c; int /*<<< orphan*/  tile_aspect; int /*<<< orphan*/  bank_height_c; int /*<<< orphan*/  bank_height; int /*<<< orphan*/  bank_width_c; int /*<<< orphan*/  bank_width; int /*<<< orphan*/  num_banks; } ;
struct TYPE_21__ {TYPE_14__ gfx9; TYPE_12__ gfx8; } ;
struct TYPE_19__ {int /*<<< orphan*/  enable; } ;
struct TYPE_16__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_17__ {int /*<<< orphan*/  surface_pitch; TYPE_10__ surface_size; } ;
struct TYPE_30__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_29__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_28__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_27__ {int /*<<< orphan*/  v_taps_c; int /*<<< orphan*/  h_taps_c; int /*<<< orphan*/  v_taps; int /*<<< orphan*/  h_taps; } ;
struct TYPE_24__ {int /*<<< orphan*/  quad_part; } ;
struct TYPE_23__ {int /*<<< orphan*/  quad_part; } ;
struct TYPE_25__ {TYPE_3__ meta_addr; TYPE_2__ addr; } ;
struct TYPE_26__ {TYPE_4__ grph; int /*<<< orphan*/  type; } ;
struct dc_plane_state {TYPE_15__ tiling_info; int /*<<< orphan*/  stereo_format; int /*<<< orphan*/  rotation; int /*<<< orphan*/  format; TYPE_13__ dcc; int /*<<< orphan*/  color_space; TYPE_11__ plane_size; TYPE_9__ clip_rect; TYPE_8__ dst_rect; TYPE_7__ src_rect; TYPE_6__ scaling_quality; TYPE_5__ address; int /*<<< orphan*/  flip_immediate; int /*<<< orphan*/  visible; } ;
struct dc {TYPE_1__* ctx; } ;
struct TYPE_22__ {int /*<<< orphan*/  logger; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SURFACE_TRACE (char*,...) ; 

void pre_surface_trace(
		struct dc *dc,
		const struct dc_plane_state *const *plane_states,
		int surface_count)
{
	int i;
	DC_LOGGER_INIT(dc->ctx->logger);

	for (i = 0; i < surface_count; i++) {
		const struct dc_plane_state *plane_state = plane_states[i];

		SURFACE_TRACE("Planes %d:\n", i);

		SURFACE_TRACE(
				"plane_state->visible = %d;\n"
				"plane_state->flip_immediate = %d;\n"
				"plane_state->address.type = %d;\n"
				"plane_state->address.grph.addr.quad_part = 0x%llX;\n"
				"plane_state->address.grph.meta_addr.quad_part = 0x%llX;\n"
				"plane_state->scaling_quality.h_taps = %d;\n"
				"plane_state->scaling_quality.v_taps = %d;\n"
				"plane_state->scaling_quality.h_taps_c = %d;\n"
				"plane_state->scaling_quality.v_taps_c = %d;\n",
				plane_state->visible,
				plane_state->flip_immediate,
				plane_state->address.type,
				plane_state->address.grph.addr.quad_part,
				plane_state->address.grph.meta_addr.quad_part,
				plane_state->scaling_quality.h_taps,
				plane_state->scaling_quality.v_taps,
				plane_state->scaling_quality.h_taps_c,
				plane_state->scaling_quality.v_taps_c);

		SURFACE_TRACE(
				"plane_state->src_rect.x = %d;\n"
				"plane_state->src_rect.y = %d;\n"
				"plane_state->src_rect.width = %d;\n"
				"plane_state->src_rect.height = %d;\n"
				"plane_state->dst_rect.x = %d;\n"
				"plane_state->dst_rect.y = %d;\n"
				"plane_state->dst_rect.width = %d;\n"
				"plane_state->dst_rect.height = %d;\n"
				"plane_state->clip_rect.x = %d;\n"
				"plane_state->clip_rect.y = %d;\n"
				"plane_state->clip_rect.width = %d;\n"
				"plane_state->clip_rect.height = %d;\n",
				plane_state->src_rect.x,
				plane_state->src_rect.y,
				plane_state->src_rect.width,
				plane_state->src_rect.height,
				plane_state->dst_rect.x,
				plane_state->dst_rect.y,
				plane_state->dst_rect.width,
				plane_state->dst_rect.height,
				plane_state->clip_rect.x,
				plane_state->clip_rect.y,
				plane_state->clip_rect.width,
				plane_state->clip_rect.height);

		SURFACE_TRACE(
				"plane_state->plane_size.surface_size.x = %d;\n"
				"plane_state->plane_size.surface_size.y = %d;\n"
				"plane_state->plane_size.surface_size.width = %d;\n"
				"plane_state->plane_size.surface_size.height = %d;\n"
				"plane_state->plane_size.surface_pitch = %d;\n",
				plane_state->plane_size.surface_size.x,
				plane_state->plane_size.surface_size.y,
				plane_state->plane_size.surface_size.width,
				plane_state->plane_size.surface_size.height,
				plane_state->plane_size.surface_pitch);


		SURFACE_TRACE(
				"plane_state->tiling_info.gfx8.num_banks = %d;\n"
				"plane_state->tiling_info.gfx8.bank_width = %d;\n"
				"plane_state->tiling_info.gfx8.bank_width_c = %d;\n"
				"plane_state->tiling_info.gfx8.bank_height = %d;\n"
				"plane_state->tiling_info.gfx8.bank_height_c = %d;\n"
				"plane_state->tiling_info.gfx8.tile_aspect = %d;\n"
				"plane_state->tiling_info.gfx8.tile_aspect_c = %d;\n"
				"plane_state->tiling_info.gfx8.tile_split = %d;\n"
				"plane_state->tiling_info.gfx8.tile_split_c = %d;\n"
				"plane_state->tiling_info.gfx8.tile_mode = %d;\n"
				"plane_state->tiling_info.gfx8.tile_mode_c = %d;\n",
				plane_state->tiling_info.gfx8.num_banks,
				plane_state->tiling_info.gfx8.bank_width,
				plane_state->tiling_info.gfx8.bank_width_c,
				plane_state->tiling_info.gfx8.bank_height,
				plane_state->tiling_info.gfx8.bank_height_c,
				plane_state->tiling_info.gfx8.tile_aspect,
				plane_state->tiling_info.gfx8.tile_aspect_c,
				plane_state->tiling_info.gfx8.tile_split,
				plane_state->tiling_info.gfx8.tile_split_c,
				plane_state->tiling_info.gfx8.tile_mode,
				plane_state->tiling_info.gfx8.tile_mode_c);

		SURFACE_TRACE(
				"plane_state->tiling_info.gfx8.pipe_config = %d;\n"
				"plane_state->tiling_info.gfx8.array_mode = %d;\n"
				"plane_state->color_space = %d;\n"
				"plane_state->dcc.enable = %d;\n"
				"plane_state->format = %d;\n"
				"plane_state->rotation = %d;\n"
				"plane_state->stereo_format = %d;\n",
				plane_state->tiling_info.gfx8.pipe_config,
				plane_state->tiling_info.gfx8.array_mode,
				plane_state->color_space,
				plane_state->dcc.enable,
				plane_state->format,
				plane_state->rotation,
				plane_state->stereo_format);

		SURFACE_TRACE("plane_state->tiling_info.gfx9.swizzle = %d;\n",
				plane_state->tiling_info.gfx9.swizzle);

		SURFACE_TRACE("\n");
	}
	SURFACE_TRACE("\n");
}