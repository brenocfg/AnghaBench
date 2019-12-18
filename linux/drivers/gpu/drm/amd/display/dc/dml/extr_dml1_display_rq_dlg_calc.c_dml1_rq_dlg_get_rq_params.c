#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct display_mode_lib {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rq_c; int /*<<< orphan*/  rq_l; } ;
struct TYPE_5__ {int /*<<< orphan*/  rq_c; int /*<<< orphan*/  rq_l; } ;
struct TYPE_4__ {int /*<<< orphan*/  rq_c; int /*<<< orphan*/  rq_l; } ;
struct _vcs_dpi_display_rq_params_st {int yuv420; int yuv420_10bpc; TYPE_3__ misc; TYPE_2__ dlg; TYPE_1__ sizing; } ;
struct _vcs_dpi_display_pipe_source_params_st {scalar_t__ source_format; } ;
typedef  enum source_format_class { ____Placeholder_source_format_class } source_format_class ;

/* Variables and functions */
 scalar_t__ dm_420_10 ; 
 scalar_t__ dm_420_8 ; 
 int /*<<< orphan*/  get_surf_rq_param (struct display_mode_lib*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct _vcs_dpi_display_pipe_source_params_st const,int) ; 
 int /*<<< orphan*/  handle_det_buf_split (struct display_mode_lib*,struct _vcs_dpi_display_rq_params_st*,struct _vcs_dpi_display_pipe_source_params_st const) ; 
 scalar_t__ is_dual_plane (int) ; 
 int /*<<< orphan*/  print__rq_params_st (struct display_mode_lib*,struct _vcs_dpi_display_rq_params_st) ; 

void dml1_rq_dlg_get_rq_params(
		struct display_mode_lib *mode_lib,
		struct _vcs_dpi_display_rq_params_st *rq_param,
		const struct _vcs_dpi_display_pipe_source_params_st pipe_src_param)
{
	/* get param for luma surface */
	rq_param->yuv420 = pipe_src_param.source_format == dm_420_8
			|| pipe_src_param.source_format == dm_420_10;
	rq_param->yuv420_10bpc = pipe_src_param.source_format == dm_420_10;

	get_surf_rq_param(
			mode_lib,
			&(rq_param->sizing.rq_l),
			&(rq_param->dlg.rq_l),
			&(rq_param->misc.rq_l),
			pipe_src_param,
			0);

	if (is_dual_plane((enum source_format_class) pipe_src_param.source_format)) {
		/* get param for chroma surface */
		get_surf_rq_param(
				mode_lib,
				&(rq_param->sizing.rq_c),
				&(rq_param->dlg.rq_c),
				&(rq_param->misc.rq_c),
				pipe_src_param,
				1);
	}

	/* calculate how to split the det buffer space between luma and chroma */
	handle_det_buf_split(mode_lib, rq_param, pipe_src_param);
	print__rq_params_st(mode_lib, *rq_param);
}