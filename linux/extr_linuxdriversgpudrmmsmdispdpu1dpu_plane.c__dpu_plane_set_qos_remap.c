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
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct drm_plane {TYPE_4__ base; TYPE_1__* dev; } ;
struct dpu_vbif_set_qos_params {int /*<<< orphan*/  clk_ctrl; int /*<<< orphan*/  is_rt; int /*<<< orphan*/  xin_id; int /*<<< orphan*/  vbif_idx; scalar_t__ num; } ;
struct dpu_plane {int /*<<< orphan*/  is_rt_pipe; TYPE_3__* pipe_hw; } ;
struct dpu_kms {int dummy; } ;
typedef  int /*<<< orphan*/  qos_params ;
struct TYPE_7__ {scalar_t__ idx; TYPE_2__* cap; } ;
struct TYPE_6__ {int /*<<< orphan*/  xin_id; int /*<<< orphan*/  clk_ctrl; } ;
struct TYPE_5__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 scalar_t__ SSPP_VIG0 ; 
 int /*<<< orphan*/  VBIF_RT ; 
 int /*<<< orphan*/  dpu_vbif_set_qos_remap (struct dpu_kms*,struct dpu_vbif_set_qos_params*) ; 
 int /*<<< orphan*/  memset (struct dpu_vbif_set_qos_params*,int /*<<< orphan*/ ,int) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

__attribute__((used)) static void _dpu_plane_set_qos_remap(struct drm_plane *plane)
{
	struct dpu_plane *pdpu;
	struct dpu_vbif_set_qos_params qos_params;
	struct msm_drm_private *priv;
	struct dpu_kms *dpu_kms;

	if (!plane || !plane->dev) {
		DPU_ERROR("invalid arguments\n");
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

	memset(&qos_params, 0, sizeof(qos_params));
	qos_params.vbif_idx = VBIF_RT;
	qos_params.clk_ctrl = pdpu->pipe_hw->cap->clk_ctrl;
	qos_params.xin_id = pdpu->pipe_hw->cap->xin_id;
	qos_params.num = pdpu->pipe_hw->idx - SSPP_VIG0;
	qos_params.is_rt = pdpu->is_rt_pipe;

	DPU_DEBUG("plane%d pipe:%d vbif:%d xin:%d rt:%d, clk_ctrl:%d\n",
			plane->base.id, qos_params.num,
			qos_params.vbif_idx,
			qos_params.xin_id, qos_params.is_rt,
			qos_params.clk_ctrl);

	dpu_vbif_set_qos_remap(dpu_kms, &qos_params);
}