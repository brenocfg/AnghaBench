#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct msm_kms {int dummy; } ;
struct msm_drm_private {int dummy; } ;
struct TYPE_24__ {int max_width; int max_height; int allow_fb_modifiers; scalar_t__ min_height; scalar_t__ min_width; } ;
struct drm_device {TYPE_3__ mode_config; struct msm_drm_private* dev_private; } ;
struct dpu_kms {int rm_init; TYPE_4__* pdev; int /*<<< orphan*/  perf; int /*<<< orphan*/  phandle; int /*<<< orphan*/  power_event; TYPE_5__* catalog; TYPE_5__* hw_intr; TYPE_5__* mmio; TYPE_5__** hw_vbif; TYPE_5__** vbif; TYPE_5__* hw_mdp; int /*<<< orphan*/  rm; struct drm_device* dev; int /*<<< orphan*/  core_rev; TYPE_5__* core_client; void* reg_dma_len; TYPE_5__* reg_dma; void** vbif_len; void* mmio_len; } ;
struct TYPE_26__ {int vbif_count; TYPE_2__* caps; TYPE_1__* vbif; } ;
struct TYPE_25__ {int /*<<< orphan*/  dev; } ;
struct TYPE_23__ {int max_mixer_width; } ;
struct TYPE_22__ {size_t id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DPU_POWER_EVENT_POST_ENABLE ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,TYPE_5__*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (TYPE_5__*) ; 
 scalar_t__ IS_ERR_OR_NULL (TYPE_5__*) ; 
 int PTR_ERR (TYPE_5__*) ; 
 size_t VBIF_NRT ; 
 size_t VBIF_RT ; 
 int /*<<< orphan*/  _dpu_kms_core_hw_rev_init (struct dpu_kms*) ; 
 int _dpu_kms_drm_obj_init (struct dpu_kms*) ; 
 int /*<<< orphan*/  _dpu_kms_get_clk (struct dpu_kms*,char*) ; 
 int /*<<< orphan*/  _dpu_kms_hw_destroy (struct dpu_kms*) ; 
 int _dpu_kms_mmu_init (struct dpu_kms*) ; 
 int /*<<< orphan*/  dpu_core_perf_destroy (int /*<<< orphan*/ *) ; 
 int dpu_core_perf_init (int /*<<< orphan*/ *,struct drm_device*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_dbg_destroy () ; 
 int dpu_dbg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_dbg_init_dbg_buses (int /*<<< orphan*/ ) ; 
 TYPE_5__* dpu_hw_catalog_init (int /*<<< orphan*/ ) ; 
 TYPE_5__* dpu_hw_intr_init (TYPE_5__*,TYPE_5__*) ; 
 TYPE_5__* dpu_hw_vbif_init (size_t,TYPE_5__*,TYPE_5__*) ; 
 void* dpu_iomap_size (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dpu_kms_handle_power_event (int /*<<< orphan*/ ,struct dpu_kms*) ; 
 TYPE_5__* dpu_power_client_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dpu_power_handle_register_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,struct dpu_kms*),struct dpu_kms*,char*) ; 
 TYPE_5__* dpu_rm_get_mdp (int /*<<< orphan*/ *) ; 
 int dpu_rm_init (int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*,struct drm_device*) ; 
 void* msm_ioremap (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct dpu_kms* to_dpu_kms (struct msm_kms*) ; 

__attribute__((used)) static int dpu_kms_hw_init(struct msm_kms *kms)
{
	struct dpu_kms *dpu_kms;
	struct drm_device *dev;
	struct msm_drm_private *priv;
	int i, rc = -EINVAL;

	if (!kms) {
		DPU_ERROR("invalid kms\n");
		goto end;
	}

	dpu_kms = to_dpu_kms(kms);
	dev = dpu_kms->dev;
	if (!dev) {
		DPU_ERROR("invalid device\n");
		goto end;
	}

	rc = dpu_dbg_init(&dpu_kms->pdev->dev);
	if (rc) {
		DRM_ERROR("failed to init dpu dbg: %d\n", rc);
		goto end;
	}

	priv = dev->dev_private;
	if (!priv) {
		DPU_ERROR("invalid private data\n");
		goto dbg_destroy;
	}

	dpu_kms->mmio = msm_ioremap(dpu_kms->pdev, "mdp", "mdp");
	if (IS_ERR(dpu_kms->mmio)) {
		rc = PTR_ERR(dpu_kms->mmio);
		DPU_ERROR("mdp register memory map failed: %d\n", rc);
		dpu_kms->mmio = NULL;
		goto error;
	}
	DRM_DEBUG("mapped dpu address space @%pK\n", dpu_kms->mmio);
	dpu_kms->mmio_len = dpu_iomap_size(dpu_kms->pdev, "mdp");

	dpu_kms->vbif[VBIF_RT] = msm_ioremap(dpu_kms->pdev, "vbif", "vbif");
	if (IS_ERR(dpu_kms->vbif[VBIF_RT])) {
		rc = PTR_ERR(dpu_kms->vbif[VBIF_RT]);
		DPU_ERROR("vbif register memory map failed: %d\n", rc);
		dpu_kms->vbif[VBIF_RT] = NULL;
		goto error;
	}
	dpu_kms->vbif_len[VBIF_RT] = dpu_iomap_size(dpu_kms->pdev, "vbif");
	dpu_kms->vbif[VBIF_NRT] = msm_ioremap(dpu_kms->pdev, "vbif_nrt", "vbif_nrt");
	if (IS_ERR(dpu_kms->vbif[VBIF_NRT])) {
		dpu_kms->vbif[VBIF_NRT] = NULL;
		DPU_DEBUG("VBIF NRT is not defined");
	} else {
		dpu_kms->vbif_len[VBIF_NRT] = dpu_iomap_size(dpu_kms->pdev,
							     "vbif_nrt");
	}

	dpu_kms->reg_dma = msm_ioremap(dpu_kms->pdev, "regdma", "regdma");
	if (IS_ERR(dpu_kms->reg_dma)) {
		dpu_kms->reg_dma = NULL;
		DPU_DEBUG("REG_DMA is not defined");
	} else {
		dpu_kms->reg_dma_len = dpu_iomap_size(dpu_kms->pdev, "regdma");
	}

	dpu_kms->core_client = dpu_power_client_create(&dpu_kms->phandle,
					"core");
	if (IS_ERR_OR_NULL(dpu_kms->core_client)) {
		rc = PTR_ERR(dpu_kms->core_client);
		if (!dpu_kms->core_client)
			rc = -EINVAL;
		DPU_ERROR("dpu power client create failed: %d\n", rc);
		dpu_kms->core_client = NULL;
		goto error;
	}

	pm_runtime_get_sync(&dpu_kms->pdev->dev);

	_dpu_kms_core_hw_rev_init(dpu_kms);

	pr_info("dpu hardware revision:0x%x\n", dpu_kms->core_rev);

	dpu_kms->catalog = dpu_hw_catalog_init(dpu_kms->core_rev);
	if (IS_ERR_OR_NULL(dpu_kms->catalog)) {
		rc = PTR_ERR(dpu_kms->catalog);
		if (!dpu_kms->catalog)
			rc = -EINVAL;
		DPU_ERROR("catalog init failed: %d\n", rc);
		dpu_kms->catalog = NULL;
		goto power_error;
	}

	dpu_dbg_init_dbg_buses(dpu_kms->core_rev);

	/*
	 * Now we need to read the HW catalog and initialize resources such as
	 * clocks, regulators, GDSC/MMAGIC, ioremap the register ranges etc
	 */
	rc = _dpu_kms_mmu_init(dpu_kms);
	if (rc) {
		DPU_ERROR("dpu_kms_mmu_init failed: %d\n", rc);
		goto power_error;
	}

	rc = dpu_rm_init(&dpu_kms->rm, dpu_kms->catalog, dpu_kms->mmio,
			dpu_kms->dev);
	if (rc) {
		DPU_ERROR("rm init failed: %d\n", rc);
		goto power_error;
	}

	dpu_kms->rm_init = true;

	dpu_kms->hw_mdp = dpu_rm_get_mdp(&dpu_kms->rm);
	if (IS_ERR_OR_NULL(dpu_kms->hw_mdp)) {
		rc = PTR_ERR(dpu_kms->hw_mdp);
		if (!dpu_kms->hw_mdp)
			rc = -EINVAL;
		DPU_ERROR("failed to get hw_mdp: %d\n", rc);
		dpu_kms->hw_mdp = NULL;
		goto power_error;
	}

	for (i = 0; i < dpu_kms->catalog->vbif_count; i++) {
		u32 vbif_idx = dpu_kms->catalog->vbif[i].id;

		dpu_kms->hw_vbif[i] = dpu_hw_vbif_init(vbif_idx,
				dpu_kms->vbif[vbif_idx], dpu_kms->catalog);
		if (IS_ERR_OR_NULL(dpu_kms->hw_vbif[vbif_idx])) {
			rc = PTR_ERR(dpu_kms->hw_vbif[vbif_idx]);
			if (!dpu_kms->hw_vbif[vbif_idx])
				rc = -EINVAL;
			DPU_ERROR("failed to init vbif %d: %d\n", vbif_idx, rc);
			dpu_kms->hw_vbif[vbif_idx] = NULL;
			goto power_error;
		}
	}

	rc = dpu_core_perf_init(&dpu_kms->perf, dev, dpu_kms->catalog,
			&dpu_kms->phandle,
			_dpu_kms_get_clk(dpu_kms, "core"));
	if (rc) {
		DPU_ERROR("failed to init perf %d\n", rc);
		goto perf_err;
	}

	dpu_kms->hw_intr = dpu_hw_intr_init(dpu_kms->mmio, dpu_kms->catalog);
	if (IS_ERR_OR_NULL(dpu_kms->hw_intr)) {
		rc = PTR_ERR(dpu_kms->hw_intr);
		DPU_ERROR("hw_intr init failed: %d\n", rc);
		dpu_kms->hw_intr = NULL;
		goto hw_intr_init_err;
	}

	/*
	 * _dpu_kms_drm_obj_init should create the DRM related objects
	 * i.e. CRTCs, planes, encoders, connectors and so forth
	 */
	rc = _dpu_kms_drm_obj_init(dpu_kms);
	if (rc) {
		DPU_ERROR("modeset init failed: %d\n", rc);
		goto drm_obj_init_err;
	}

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	/*
	 * max crtc width is equal to the max mixer width * 2 and max height is
	 * is 4K
	 */
	dev->mode_config.max_width =
			dpu_kms->catalog->caps->max_mixer_width * 2;
	dev->mode_config.max_height = 4096;

	/*
	 * Support format modifiers for compression etc.
	 */
	dev->mode_config.allow_fb_modifiers = true;

	/*
	 * Handle (re)initializations during power enable
	 */
	dpu_kms_handle_power_event(DPU_POWER_EVENT_POST_ENABLE, dpu_kms);
	dpu_kms->power_event = dpu_power_handle_register_event(
			&dpu_kms->phandle,
			DPU_POWER_EVENT_POST_ENABLE,
			dpu_kms_handle_power_event, dpu_kms, "kms");

	pm_runtime_put_sync(&dpu_kms->pdev->dev);

	return 0;

drm_obj_init_err:
	dpu_core_perf_destroy(&dpu_kms->perf);
hw_intr_init_err:
perf_err:
power_error:
	pm_runtime_put_sync(&dpu_kms->pdev->dev);
error:
	_dpu_kms_hw_destroy(dpu_kms);
dbg_destroy:
	dpu_dbg_destroy();
end:
	return rc;
}