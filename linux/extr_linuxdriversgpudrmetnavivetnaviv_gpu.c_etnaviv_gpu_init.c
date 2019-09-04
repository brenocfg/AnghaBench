#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_13__ {int /*<<< orphan*/ * suballoc; } ;
struct TYPE_11__ {scalar_t__ model; int features; int minor_features0; int minor_features7; int minor_features10; } ;
struct etnaviv_gpu {int exec_state; int /*<<< orphan*/  dev; TYPE_2__* mmu; TYPE_6__ buffer; int /*<<< orphan*/  lock; int /*<<< orphan*/  event_free; int /*<<< orphan*/  event; int /*<<< orphan*/  event_bitmap; int /*<<< orphan*/  event_spinlock; TYPE_2__* cmdbuf_suballoc; int /*<<< orphan*/  sec_mode; TYPE_1__ identity; scalar_t__ memory_base; } ;
struct TYPE_12__ {scalar_t__ version; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ ETNAVIV_IOMMU_V1 ; 
 int /*<<< orphan*/  ETNA_NR_EVENTS ; 
 int /*<<< orphan*/  ETNA_SEC_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PHYS_OFFSET ; 
 int PTR_ERR (TYPE_2__*) ; 
 scalar_t__ SZ_2G ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int chipFeatures_FAST_CLEAR ; 
 int chipFeatures_FE20 ; 
 int chipFeatures_PIPE_3D ; 
 int chipFeatures_PIPE_VG ; 
 int chipMinorFeatures0_MC20 ; 
 int chipMinorFeatures10_SECURITY_AHB ; 
 int chipMinorFeatures7_BIT_SECURITY ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_get_required_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_cmdbuf_free (TYPE_6__*) ; 
 int etnaviv_cmdbuf_get_va (TYPE_6__*) ; 
 int etnaviv_cmdbuf_init (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* etnaviv_cmdbuf_suballoc_new (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_gpu_hw_init (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_hw_identify (struct etnaviv_gpu*) ; 
 int etnaviv_hw_reset (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_iommu_destroy (TYPE_2__*) ; 
 TYPE_2__* etnaviv_iommu_new (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int etnaviv_gpu_init(struct etnaviv_gpu *gpu)
{
	int ret, i;

	ret = pm_runtime_get_sync(gpu->dev);
	if (ret < 0) {
		dev_err(gpu->dev, "Failed to enable GPU power domain\n");
		return ret;
	}

	etnaviv_hw_identify(gpu);

	if (gpu->identity.model == 0) {
		dev_err(gpu->dev, "Unknown GPU model\n");
		ret = -ENXIO;
		goto fail;
	}

	/* Exclude VG cores with FE2.0 */
	if (gpu->identity.features & chipFeatures_PIPE_VG &&
	    gpu->identity.features & chipFeatures_FE20) {
		dev_info(gpu->dev, "Ignoring GPU with VG and FE2.0\n");
		ret = -ENXIO;
		goto fail;
	}

	/*
	 * Set the GPU linear window to be at the end of the DMA window, where
	 * the CMA area is likely to reside. This ensures that we are able to
	 * map the command buffers while having the linear window overlap as
	 * much RAM as possible, so we can optimize mappings for other buffers.
	 *
	 * For 3D cores only do this if MC2.0 is present, as with MC1.0 it leads
	 * to different views of the memory on the individual engines.
	 */
	if (!(gpu->identity.features & chipFeatures_PIPE_3D) ||
	    (gpu->identity.minor_features0 & chipMinorFeatures0_MC20)) {
		u32 dma_mask = (u32)dma_get_required_mask(gpu->dev);
		if (dma_mask < PHYS_OFFSET + SZ_2G)
			gpu->memory_base = PHYS_OFFSET;
		else
			gpu->memory_base = dma_mask - SZ_2G + 1;
	} else if (PHYS_OFFSET >= SZ_2G) {
		dev_info(gpu->dev, "Need to move linear window on MC1.0, disabling TS\n");
		gpu->memory_base = PHYS_OFFSET;
		gpu->identity.features &= ~chipFeatures_FAST_CLEAR;
	}

	/*
	 * On cores with security features supported, we claim control over the
	 * security states.
	 */
	if ((gpu->identity.minor_features7 & chipMinorFeatures7_BIT_SECURITY) &&
	    (gpu->identity.minor_features10 & chipMinorFeatures10_SECURITY_AHB))
		gpu->sec_mode = ETNA_SEC_KERNEL;

	ret = etnaviv_hw_reset(gpu);
	if (ret) {
		dev_err(gpu->dev, "GPU reset failed\n");
		goto fail;
	}

	gpu->mmu = etnaviv_iommu_new(gpu);
	if (IS_ERR(gpu->mmu)) {
		dev_err(gpu->dev, "Failed to instantiate GPU IOMMU\n");
		ret = PTR_ERR(gpu->mmu);
		goto fail;
	}

	gpu->cmdbuf_suballoc = etnaviv_cmdbuf_suballoc_new(gpu);
	if (IS_ERR(gpu->cmdbuf_suballoc)) {
		dev_err(gpu->dev, "Failed to create cmdbuf suballocator\n");
		ret = PTR_ERR(gpu->cmdbuf_suballoc);
		goto fail;
	}

	/* Create buffer: */
	ret = etnaviv_cmdbuf_init(gpu->cmdbuf_suballoc, &gpu->buffer,
				  PAGE_SIZE);
	if (ret) {
		dev_err(gpu->dev, "could not create command buffer\n");
		goto destroy_iommu;
	}

	if (gpu->mmu->version == ETNAVIV_IOMMU_V1 &&
	    etnaviv_cmdbuf_get_va(&gpu->buffer) > 0x80000000) {
		ret = -EINVAL;
		dev_err(gpu->dev,
			"command buffer outside valid memory window\n");
		goto free_buffer;
	}

	/* Setup event management */
	spin_lock_init(&gpu->event_spinlock);
	init_completion(&gpu->event_free);
	bitmap_zero(gpu->event_bitmap, ETNA_NR_EVENTS);
	for (i = 0; i < ARRAY_SIZE(gpu->event); i++)
		complete(&gpu->event_free);

	/* Now program the hardware */
	mutex_lock(&gpu->lock);
	etnaviv_gpu_hw_init(gpu);
	gpu->exec_state = -1;
	mutex_unlock(&gpu->lock);

	pm_runtime_mark_last_busy(gpu->dev);
	pm_runtime_put_autosuspend(gpu->dev);

	return 0;

free_buffer:
	etnaviv_cmdbuf_free(&gpu->buffer);
	gpu->buffer.suballoc = NULL;
destroy_iommu:
	etnaviv_iommu_destroy(gpu->mmu);
	gpu->mmu = NULL;
fail:
	pm_runtime_mark_last_busy(gpu->dev);
	pm_runtime_put_autosuspend(gpu->dev);

	return ret;
}