#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  vrefresh; } ;
struct drm_crtc {TYPE_3__ mode; } ;
struct dpu_vbif_set_ot_params {int is_wfd; int rd; int /*<<< orphan*/  clk_ctrl; int /*<<< orphan*/  vbif_idx; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ num; int /*<<< orphan*/  xin_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  src_rect; } ;
struct dpu_plane {TYPE_5__* pipe_hw; int /*<<< orphan*/  is_rt_pipe; TYPE_2__ pipe_cfg; } ;
struct dpu_kms {int dummy; } ;
typedef  int /*<<< orphan*/  ot_params ;
struct TYPE_10__ {TYPE_4__* cap; scalar_t__ idx; } ;
struct TYPE_9__ {int /*<<< orphan*/  clk_ctrl; int /*<<< orphan*/  xin_id; } ;
struct TYPE_6__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 scalar_t__ SSPP_NONE ; 
 int /*<<< orphan*/  VBIF_RT ; 
 int /*<<< orphan*/  dpu_vbif_set_ot_limit (struct dpu_kms*,struct dpu_vbif_set_ot_params*) ; 
 int /*<<< orphan*/  drm_rect_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_rect_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dpu_vbif_set_ot_params*,int /*<<< orphan*/ ,int) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

__attribute__((used)) static void _dpu_plane_set_ot_limit(struct drm_plane *plane,
		struct drm_crtc *crtc)
{
	struct dpu_plane *pdpu;
	struct dpu_vbif_set_ot_params ot_params;
	struct msm_drm_private *priv;
	struct dpu_kms *dpu_kms;

	if (!plane || !plane->dev || !crtc) {
		DPU_ERROR("invalid arguments plane %d crtc %d\n",
				plane != 0, crtc != 0);
		return;
	}

	priv = plane->dev->dev_private;
	if (!priv || !priv->kms) {
		DPU_ERROR("invalid KMS reference\n");
		return;
	}

	dpu_kms = to_dpu_kms(priv->kms);
	pdpu = to_dpu_plane(plane);
	if (!pdpu->pipe_hw) {
		DPU_ERROR("invalid pipe reference\n");
		return;
	}

	memset(&ot_params, 0, sizeof(ot_params));
	ot_params.xin_id = pdpu->pipe_hw->cap->xin_id;
	ot_params.num = pdpu->pipe_hw->idx - SSPP_NONE;
	ot_params.width = drm_rect_width(&pdpu->pipe_cfg.src_rect);
	ot_params.height = drm_rect_height(&pdpu->pipe_cfg.src_rect);
	ot_params.is_wfd = !pdpu->is_rt_pipe;
	ot_params.frame_rate = crtc->mode.vrefresh;
	ot_params.vbif_idx = VBIF_RT;
	ot_params.clk_ctrl = pdpu->pipe_hw->cap->clk_ctrl;
	ot_params.rd = true;

	dpu_vbif_set_ot_limit(dpu_kms, &ot_params);
}