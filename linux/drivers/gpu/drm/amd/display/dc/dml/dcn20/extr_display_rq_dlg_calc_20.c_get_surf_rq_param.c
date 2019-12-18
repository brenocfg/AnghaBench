#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct display_mode_lib {int dummy; } ;
struct TYPE_6__ {unsigned int viewport_width_c; unsigned int viewport_height_c; unsigned int data_pitch_c; unsigned int meta_pitch_c; unsigned int viewport_width; unsigned int viewport_height; unsigned int data_pitch; unsigned int meta_pitch; int /*<<< orphan*/  source_scan; int /*<<< orphan*/  macro_tile_size; int /*<<< orphan*/  sw_mode; int /*<<< orphan*/  source_format; } ;
typedef  TYPE_1__ display_pipe_source_params_st ;
struct TYPE_7__ {int chunk_bytes; int min_chunk_bytes; int meta_chunk_bytes; int min_meta_chunk_bytes; int mpte_group_bytes; } ;
typedef  TYPE_2__ display_data_rq_sizing_params_st ;
typedef  int /*<<< orphan*/  display_data_rq_misc_params_st ;
typedef  int /*<<< orphan*/  display_data_rq_dlg_params_st ;

/* Variables and functions */
 int /*<<< orphan*/  get_meta_and_pte_attr (struct display_mode_lib*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void get_surf_rq_param(struct display_mode_lib *mode_lib,
		display_data_rq_sizing_params_st *rq_sizing_param,
		display_data_rq_dlg_params_st *rq_dlg_param,
		display_data_rq_misc_params_st *rq_misc_param,
		const display_pipe_source_params_st pipe_src_param,
		bool is_chroma)
{
	bool mode_422 = 0;
	unsigned int vp_width = 0;
	unsigned int vp_height = 0;
	unsigned int data_pitch = 0;
	unsigned int meta_pitch = 0;
	unsigned int ppe = mode_422 ? 2 : 1;

	// FIXME check if ppe apply for both luma and chroma in 422 case
	if (is_chroma) {
		vp_width = pipe_src_param.viewport_width_c / ppe;
		vp_height = pipe_src_param.viewport_height_c;
		data_pitch = pipe_src_param.data_pitch_c;
		meta_pitch = pipe_src_param.meta_pitch_c;
	} else {
		vp_width = pipe_src_param.viewport_width / ppe;
		vp_height = pipe_src_param.viewport_height;
		data_pitch = pipe_src_param.data_pitch;
		meta_pitch = pipe_src_param.meta_pitch;
	}

	rq_sizing_param->chunk_bytes = 8192;

	if (rq_sizing_param->chunk_bytes == 64 * 1024)
		rq_sizing_param->min_chunk_bytes = 0;
	else
		rq_sizing_param->min_chunk_bytes = 1024;

	rq_sizing_param->meta_chunk_bytes = 2048;
	rq_sizing_param->min_meta_chunk_bytes = 256;

	rq_sizing_param->mpte_group_bytes = 2048;

	get_meta_and_pte_attr(mode_lib,
			rq_dlg_param,
			rq_misc_param,
			rq_sizing_param,
			vp_width,
			vp_height,
			data_pitch,
			meta_pitch,
			pipe_src_param.source_format,
			pipe_src_param.sw_mode,
			pipe_src_param.macro_tile_size,
			pipe_src_param.source_scan,
			is_chroma);
}