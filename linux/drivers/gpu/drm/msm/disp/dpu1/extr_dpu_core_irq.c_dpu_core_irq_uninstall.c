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
struct msm_drm_private {int dummy; } ;
struct TYPE_6__ {int total_irqs; int /*<<< orphan*/ * irq_counts; int /*<<< orphan*/ * enable_counts; int /*<<< orphan*/ * irq_cb_tbl; } ;
struct dpu_kms {TYPE_3__ irq_obj; TYPE_2__* pdev; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_clear_all_irqs (struct dpu_kms*) ; 
 int /*<<< orphan*/  dpu_disable_all_irqs (struct dpu_kms*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

void dpu_core_irq_uninstall(struct dpu_kms *dpu_kms)
{
	struct msm_drm_private *priv;
	int i;

	if (!dpu_kms->dev) {
		DPU_ERROR("invalid drm device\n");
		return;
	} else if (!dpu_kms->dev->dev_private) {
		DPU_ERROR("invalid device private\n");
		return;
	}
	priv = dpu_kms->dev->dev_private;

	pm_runtime_get_sync(&dpu_kms->pdev->dev);
	for (i = 0; i < dpu_kms->irq_obj.total_irqs; i++)
		if (atomic_read(&dpu_kms->irq_obj.enable_counts[i]) ||
				!list_empty(&dpu_kms->irq_obj.irq_cb_tbl[i]))
			DPU_ERROR("irq_idx=%d still enabled/registered\n", i);

	dpu_clear_all_irqs(dpu_kms);
	dpu_disable_all_irqs(dpu_kms);
	pm_runtime_put_sync(&dpu_kms->pdev->dev);

	kfree(dpu_kms->irq_obj.irq_cb_tbl);
	kfree(dpu_kms->irq_obj.enable_counts);
	kfree(dpu_kms->irq_obj.irq_counts);
	dpu_kms->irq_obj.irq_cb_tbl = NULL;
	dpu_kms->irq_obj.enable_counts = NULL;
	dpu_kms->irq_obj.irq_counts = NULL;
	dpu_kms->irq_obj.total_irqs = 0;
}