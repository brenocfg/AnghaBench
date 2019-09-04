#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct drm_plane {TYPE_2__* dev; } ;
struct dpu_plane {int /*<<< orphan*/  is_rt_pipe; } ;
struct dpu_kms {TYPE_1__* pdev; } ;
struct TYPE_4__ {struct msm_drm_private* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_PLANE_QOS_PANIC_CTRL ; 
 int EINVAL ; 
 int /*<<< orphan*/  _dpu_plane_set_qos_ctrl (struct drm_plane*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

int dpu_plane_danger_signal_ctrl(struct drm_plane *plane, bool enable)
{
	struct dpu_plane *pdpu;
	struct msm_drm_private *priv;
	struct dpu_kms *dpu_kms;

	if (!plane || !plane->dev) {
		DPU_ERROR("invalid arguments\n");
		return -EINVAL;
	}

	priv = plane->dev->dev_private;
	if (!priv || !priv->kms) {
		DPU_ERROR("invalid KMS reference\n");
		return -EINVAL;
	}

	dpu_kms = to_dpu_kms(priv->kms);
	pdpu = to_dpu_plane(plane);

	if (!pdpu->is_rt_pipe)
		goto end;

	pm_runtime_get_sync(&dpu_kms->pdev->dev);
	_dpu_plane_set_qos_ctrl(plane, enable, DPU_PLANE_QOS_PANIC_CTRL);
	pm_runtime_put_sync(&dpu_kms->pdev->dev);

end:
	return 0;
}