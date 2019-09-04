#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct msm_format {int dummy; } ;
struct drm_rect {int x1; int y1; int x2; int y2; } ;
struct drm_plane_state {int src_x; int src_y; int src_w; int src_h; TYPE_4__* plane; int /*<<< orphan*/  fb; } ;
struct dpu_plane_state {void* multirect_index; void* multirect_mode; } ;
struct dpu_plane {scalar_t__ is_virtual; TYPE_2__* pipe_sblk; } ;
struct dpu_multirect_plane_states {struct drm_plane_state* r0; struct drm_plane_state* r1; } ;
struct dpu_format {unsigned int tile_height; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_3__ base; } ;
struct TYPE_6__ {TYPE_1__* common; } ;
struct TYPE_5__ {int maxlinewidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_PLANE (struct dpu_plane*,char*,void*,void*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DPU_ERROR_PLANE (struct dpu_plane*,char*) ; 
 scalar_t__ DPU_FORMAT_IS_UBWC (struct dpu_format const*) ; 
 scalar_t__ DPU_FORMAT_IS_YUV (struct dpu_format const*) ; 
 void* DPU_SSPP_MULTIRECT_PARALLEL ; 
 void* DPU_SSPP_MULTIRECT_TIME_MX ; 
 void* DPU_SSPP_RECT_0 ; 
 void* DPU_SSPP_RECT_1 ; 
 int EINVAL ; 
 size_t R0 ; 
 size_t R1 ; 
 int R_MAX ; 
 struct drm_rect drm_plane_state_dest (struct drm_plane_state const*) ; 
 int drm_rect_calc_hscale (struct drm_rect*,struct drm_rect*,int,int) ; 
 int drm_rect_calc_vscale (struct drm_rect*,struct drm_rect*,int,int) ; 
 int drm_rect_width (struct drm_rect*) ; 
 struct msm_format* msm_framebuffer_format (int /*<<< orphan*/ ) ; 
 struct dpu_format* to_dpu_format (struct msm_format const*) ; 
 struct dpu_plane* to_dpu_plane (TYPE_4__*) ; 
 struct dpu_plane_state* to_dpu_plane_state (struct drm_plane_state const*) ; 

int dpu_plane_validate_multirect_v2(struct dpu_multirect_plane_states *plane)
{
	struct dpu_plane_state *pstate[R_MAX];
	const struct drm_plane_state *drm_state[R_MAX];
	struct drm_rect src[R_MAX], dst[R_MAX];
	struct dpu_plane *dpu_plane[R_MAX];
	const struct dpu_format *fmt[R_MAX];
	int i, buffer_lines;
	unsigned int max_tile_height = 1;
	bool parallel_fetch_qualified = true;
	bool has_tiled_rect = false;

	for (i = 0; i < R_MAX; i++) {
		const struct msm_format *msm_fmt;

		drm_state[i] = i ? plane->r1 : plane->r0;
		msm_fmt = msm_framebuffer_format(drm_state[i]->fb);
		fmt[i] = to_dpu_format(msm_fmt);

		if (DPU_FORMAT_IS_UBWC(fmt[i])) {
			has_tiled_rect = true;
			if (fmt[i]->tile_height > max_tile_height)
				max_tile_height = fmt[i]->tile_height;
		}
	}

	for (i = 0; i < R_MAX; i++) {
		int width_threshold;

		pstate[i] = to_dpu_plane_state(drm_state[i]);
		dpu_plane[i] = to_dpu_plane(drm_state[i]->plane);

		if (pstate[i] == NULL) {
			DPU_ERROR("DPU plane state of plane id %d is NULL\n",
				drm_state[i]->plane->base.id);
			return -EINVAL;
		}

		src[i].x1 = drm_state[i]->src_x >> 16;
		src[i].y1 = drm_state[i]->src_y >> 16;
		src[i].x2 = src[i].x1 + (drm_state[i]->src_w >> 16);
		src[i].y2 = src[i].y1 + (drm_state[i]->src_h >> 16);

		dst[i] = drm_plane_state_dest(drm_state[i]);

		if (drm_rect_calc_hscale(&src[i], &dst[i], 1, 1) != 1 ||
		    drm_rect_calc_vscale(&src[i], &dst[i], 1, 1) != 1) {
			DPU_ERROR_PLANE(dpu_plane[i],
				"scaling is not supported in multirect mode\n");
			return -EINVAL;
		}

		if (DPU_FORMAT_IS_YUV(fmt[i])) {
			DPU_ERROR_PLANE(dpu_plane[i],
				"Unsupported format for multirect mode\n");
			return -EINVAL;
		}

		/**
		 * SSPP PD_MEM is split half - one for each RECT.
		 * Tiled formats need 5 lines of buffering while fetching
		 * whereas linear formats need only 2 lines.
		 * So we cannot support more than half of the supported SSPP
		 * width for tiled formats.
		 */
		width_threshold = dpu_plane[i]->pipe_sblk->common->maxlinewidth;
		if (has_tiled_rect)
			width_threshold /= 2;

		if (parallel_fetch_qualified &&
		    drm_rect_width(&src[i]) > width_threshold)
			parallel_fetch_qualified = false;

	}

	/* Validate RECT's and set the mode */

	/* Prefer PARALLEL FETCH Mode over TIME_MX Mode */
	if (parallel_fetch_qualified) {
		pstate[R0]->multirect_mode = DPU_SSPP_MULTIRECT_PARALLEL;
		pstate[R1]->multirect_mode = DPU_SSPP_MULTIRECT_PARALLEL;

		goto done;
	}

	/* TIME_MX Mode */
	buffer_lines = 2 * max_tile_height;

	if (dst[R1].y1 >= dst[R0].y2 + buffer_lines ||
	    dst[R0].y1 >= dst[R1].y2 + buffer_lines) {
		pstate[R0]->multirect_mode = DPU_SSPP_MULTIRECT_TIME_MX;
		pstate[R1]->multirect_mode = DPU_SSPP_MULTIRECT_TIME_MX;
	} else {
		DPU_ERROR(
			"No multirect mode possible for the planes (%d - %d)\n",
			drm_state[R0]->plane->base.id,
			drm_state[R1]->plane->base.id);
		return -EINVAL;
	}

done:
	if (dpu_plane[R0]->is_virtual) {
		pstate[R0]->multirect_index = DPU_SSPP_RECT_1;
		pstate[R1]->multirect_index = DPU_SSPP_RECT_0;
	} else {
		pstate[R0]->multirect_index = DPU_SSPP_RECT_0;
		pstate[R1]->multirect_index = DPU_SSPP_RECT_1;
	};

	DPU_DEBUG_PLANE(dpu_plane[R0], "R0: %d - %d\n",
		pstate[R0]->multirect_mode, pstate[R0]->multirect_index);
	DPU_DEBUG_PLANE(dpu_plane[R1], "R1: %d - %d\n",
		pstate[R1]->multirect_mode, pstate[R1]->multirect_index);
	return 0;
}