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
struct msm_kms {int irq; } ;
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct dpu_kms {struct msm_kms base; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int EINVAL ; 
 struct msm_kms* ERR_PTR (int) ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 

struct msm_kms *dpu_kms_init(struct drm_device *dev)
{
	struct msm_drm_private *priv;
	struct dpu_kms *dpu_kms;
	int irq;

	if (!dev || !dev->dev_private) {
		DPU_ERROR("drm device node invalid\n");
		return ERR_PTR(-EINVAL);
	}

	priv = dev->dev_private;
	dpu_kms = to_dpu_kms(priv->kms);

	irq = irq_of_parse_and_map(dpu_kms->pdev->dev.of_node, 0);
	if (irq < 0) {
		DPU_ERROR("failed to get irq: %d\n", irq);
		return ERR_PTR(irq);
	}
	dpu_kms->base.irq = irq;

	return &dpu_kms->base;
}