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
typedef  size_t u32 ;
struct drm_device {int dummy; } ;
struct dpu_kms {int rm_init; int /*<<< orphan*/ * mmio; TYPE_2__* pdev; int /*<<< orphan*/ * hw_mdp; int /*<<< orphan*/ ** vbif; TYPE_3__* catalog; int /*<<< orphan*/  rm; scalar_t__* hw_vbif; int /*<<< orphan*/ * hw_intr; struct drm_device* dev; } ;
struct TYPE_6__ {int vbif_count; TYPE_1__* vbif; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {size_t id; } ;

/* Variables and functions */
 size_t VBIF_MAX ; 
 size_t VBIF_NRT ; 
 size_t VBIF_RT ; 
 int /*<<< orphan*/  _dpu_kms_mmu_destroy (struct dpu_kms*) ; 
 int /*<<< orphan*/  devm_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_hw_catalog_deinit (TYPE_3__*) ; 
 int /*<<< orphan*/  dpu_hw_intr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_hw_mdp_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_hw_vbif_destroy (scalar_t__) ; 
 int /*<<< orphan*/  dpu_rm_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _dpu_kms_hw_destroy(struct dpu_kms *dpu_kms)
{
	struct drm_device *dev;
	int i;

	dev = dpu_kms->dev;
	if (!dev)
		return;

	if (dpu_kms->hw_intr)
		dpu_hw_intr_destroy(dpu_kms->hw_intr);
	dpu_kms->hw_intr = NULL;

	/* safe to call these more than once during shutdown */
	_dpu_kms_mmu_destroy(dpu_kms);

	if (dpu_kms->catalog) {
		for (i = 0; i < dpu_kms->catalog->vbif_count; i++) {
			u32 vbif_idx = dpu_kms->catalog->vbif[i].id;

			if ((vbif_idx < VBIF_MAX) && dpu_kms->hw_vbif[vbif_idx])
				dpu_hw_vbif_destroy(dpu_kms->hw_vbif[vbif_idx]);
		}
	}

	if (dpu_kms->rm_init)
		dpu_rm_destroy(&dpu_kms->rm);
	dpu_kms->rm_init = false;

	if (dpu_kms->catalog)
		dpu_hw_catalog_deinit(dpu_kms->catalog);
	dpu_kms->catalog = NULL;

	if (dpu_kms->vbif[VBIF_NRT])
		devm_iounmap(&dpu_kms->pdev->dev, dpu_kms->vbif[VBIF_NRT]);
	dpu_kms->vbif[VBIF_NRT] = NULL;

	if (dpu_kms->vbif[VBIF_RT])
		devm_iounmap(&dpu_kms->pdev->dev, dpu_kms->vbif[VBIF_RT]);
	dpu_kms->vbif[VBIF_RT] = NULL;

	if (dpu_kms->hw_mdp)
		dpu_hw_mdp_destroy(dpu_kms->hw_mdp);
	dpu_kms->hw_mdp = NULL;

	if (dpu_kms->mmio)
		devm_iounmap(&dpu_kms->pdev->dev, dpu_kms->mmio);
	dpu_kms->mmio = NULL;
}