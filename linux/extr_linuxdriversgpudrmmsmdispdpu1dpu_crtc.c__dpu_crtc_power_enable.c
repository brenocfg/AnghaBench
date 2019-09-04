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
struct drm_crtc {TYPE_2__* dev; } ;
struct dpu_kms {TYPE_1__* pdev; } ;
struct dpu_crtc {struct drm_crtc base; } ;
struct TYPE_4__ {struct msm_drm_private* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int _dpu_crtc_power_enable(struct dpu_crtc *dpu_crtc, bool enable)
{
	struct drm_crtc *crtc;
	struct msm_drm_private *priv;
	struct dpu_kms *dpu_kms;

	if (!dpu_crtc) {
		DPU_ERROR("invalid dpu crtc\n");
		return -EINVAL;
	}

	crtc = &dpu_crtc->base;
	if (!crtc->dev || !crtc->dev->dev_private) {
		DPU_ERROR("invalid drm device\n");
		return -EINVAL;
	}

	priv = crtc->dev->dev_private;
	if (!priv->kms) {
		DPU_ERROR("invalid kms\n");
		return -EINVAL;
	}

	dpu_kms = to_dpu_kms(priv->kms);

	if (enable)
		pm_runtime_get_sync(&dpu_kms->pdev->dev);
	else
		pm_runtime_put_sync(&dpu_kms->pdev->dev);

	return 0;
}