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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
struct drm_plane {TYPE_5__ base; } ;
struct drm_framebuffer {int /*<<< orphan*/  modifier; TYPE_1__* format; } ;
struct TYPE_18__ {int /*<<< orphan*/  creq_lut; } ;
struct TYPE_11__ {int /*<<< orphan*/  src_rect; } ;
struct dpu_plane {TYPE_9__ pipe_qos_cfg; TYPE_8__* pipe_hw; int /*<<< orphan*/  is_rt_pipe; scalar_t__ pipe; TYPE_4__* catalog; TYPE_2__ pipe_cfg; } ;
struct TYPE_15__ {int /*<<< orphan*/  pixel_format; } ;
struct dpu_format {TYPE_6__ base; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* setup_creq_lut ) (TYPE_8__*,TYPE_9__*) ;} ;
struct TYPE_17__ {TYPE_7__ ops; } ;
struct TYPE_12__ {int /*<<< orphan*/ * qos_lut_tbl; } ;
struct TYPE_13__ {TYPE_3__ perf; } ;
struct TYPE_10__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ DPU_FORMAT_IS_LINEAR (struct dpu_format const*) ; 
 size_t DPU_QOS_LUT_USAGE_LINEAR ; 
 size_t DPU_QOS_LUT_USAGE_MACROTILE ; 
 size_t DPU_QOS_LUT_USAGE_NRT ; 
 scalar_t__ SSPP_VIG0 ; 
 size_t _dpu_plane_calc_fill_level (struct drm_plane*,struct dpu_format const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dpu_plane_get_qos_lut (int /*<<< orphan*/ *,size_t) ; 
 struct dpu_format* dpu_get_dpu_format_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_rect_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,TYPE_9__*) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  trace_dpu_perf_set_qos_luts (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void _dpu_plane_set_qos_lut(struct drm_plane *plane,
		struct drm_framebuffer *fb)
{
	struct dpu_plane *pdpu = to_dpu_plane(plane);
	const struct dpu_format *fmt = NULL;
	u64 qos_lut;
	u32 total_fl = 0, lut_usage;

	if (!pdpu->is_rt_pipe) {
		lut_usage = DPU_QOS_LUT_USAGE_NRT;
	} else {
		fmt = dpu_get_dpu_format_ext(
				fb->format->format,
				fb->modifier);
		total_fl = _dpu_plane_calc_fill_level(plane, fmt,
				drm_rect_width(&pdpu->pipe_cfg.src_rect));

		if (fmt && DPU_FORMAT_IS_LINEAR(fmt))
			lut_usage = DPU_QOS_LUT_USAGE_LINEAR;
		else
			lut_usage = DPU_QOS_LUT_USAGE_MACROTILE;
	}

	qos_lut = _dpu_plane_get_qos_lut(
			&pdpu->catalog->perf.qos_lut_tbl[lut_usage], total_fl);

	pdpu->pipe_qos_cfg.creq_lut = qos_lut;

	trace_dpu_perf_set_qos_luts(pdpu->pipe - SSPP_VIG0,
			(fmt) ? fmt->base.pixel_format : 0,
			pdpu->is_rt_pipe, total_fl, qos_lut, lut_usage);

	DPU_DEBUG("plane%u: pnum:%d fmt: %4.4s rt:%d fl:%u lut:0x%llx\n",
			plane->base.id,
			pdpu->pipe - SSPP_VIG0,
			fmt ? (char *)&fmt->base.pixel_format : NULL,
			pdpu->is_rt_pipe, total_fl, qos_lut);

	pdpu->pipe_hw->ops.setup_creq_lut(pdpu->pipe_hw, &pdpu->pipe_qos_cfg);
}