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
struct drm_encoder {TYPE_2__* dev; } ;
struct dpu_kms {TYPE_1__* pdev; } ;
struct dpu_encoder_virt {struct drm_encoder base; } ;
struct TYPE_4__ {struct msm_drm_private* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int _dpu_encoder_power_enable(struct dpu_encoder_virt *dpu_enc,
								bool enable)
{
	struct drm_encoder *drm_enc;
	struct msm_drm_private *priv;
	struct dpu_kms *dpu_kms;

	if (!dpu_enc) {
		DPU_ERROR("invalid dpu enc\n");
		return -EINVAL;
	}

	drm_enc = &dpu_enc->base;
	if (!drm_enc->dev || !drm_enc->dev->dev_private) {
		DPU_ERROR("drm device invalid\n");
		return -EINVAL;
	}

	priv = drm_enc->dev->dev_private;
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