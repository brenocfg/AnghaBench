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
struct drm_plane {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  mode; } ;
struct dpu_vbif_set_ot_params {int is_wfd; int rd; int /*<<< orphan*/  clk_ctrl; int /*<<< orphan*/  vbif_idx; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ num; int /*<<< orphan*/  xin_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  src_rect; } ;
struct dpu_plane {TYPE_3__* pipe_hw; int /*<<< orphan*/  is_rt_pipe; TYPE_1__ pipe_cfg; } ;
struct dpu_kms {int dummy; } ;
typedef  int /*<<< orphan*/  ot_params ;
struct TYPE_6__ {TYPE_2__* cap; scalar_t__ idx; } ;
struct TYPE_5__ {int /*<<< orphan*/  clk_ctrl; int /*<<< orphan*/  xin_id; } ;

/* Variables and functions */
 scalar_t__ SSPP_NONE ; 
 int /*<<< orphan*/  VBIF_RT ; 
 struct dpu_kms* _dpu_plane_get_kms (struct drm_plane*) ; 
 int /*<<< orphan*/  dpu_vbif_set_ot_limit (struct dpu_kms*,struct dpu_vbif_set_ot_params*) ; 
 int /*<<< orphan*/  drm_mode_vrefresh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_rect_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_rect_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dpu_vbif_set_ot_params*,int /*<<< orphan*/ ,int) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

__attribute__((used)) static void _dpu_plane_set_ot_limit(struct drm_plane *plane,
		struct drm_crtc *crtc)
{
	struct dpu_plane *pdpu = to_dpu_plane(plane);
	struct dpu_vbif_set_ot_params ot_params;
	struct dpu_kms *dpu_kms = _dpu_plane_get_kms(plane);

	memset(&ot_params, 0, sizeof(ot_params));
	ot_params.xin_id = pdpu->pipe_hw->cap->xin_id;
	ot_params.num = pdpu->pipe_hw->idx - SSPP_NONE;
	ot_params.width = drm_rect_width(&pdpu->pipe_cfg.src_rect);
	ot_params.height = drm_rect_height(&pdpu->pipe_cfg.src_rect);
	ot_params.is_wfd = !pdpu->is_rt_pipe;
	ot_params.frame_rate = drm_mode_vrefresh(&crtc->mode);
	ot_params.vbif_idx = VBIF_RT;
	ot_params.clk_ctrl = pdpu->pipe_hw->cap->clk_ctrl;
	ot_params.rd = true;

	dpu_vbif_set_ot_limit(dpu_kms, &ot_params);
}