#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_rbmemptrs {int dummy; } ;
struct msm_gpu_funcs {int dummy; } ;
struct msm_gpu_config {int nr_rings; int /*<<< orphan*/  va_end; int /*<<< orphan*/  va_start; int /*<<< orphan*/  ioname; } ;
struct msm_gpu {int num_perfcntrs; void** last_cntrs; char const* name; void* mmio; int irq; void* ebi1_clk; void* gpu_reg; void* gpu_cx; void* aspace; void** rb; int nr_rings; int /*<<< orphan*/  memptrs_bo; struct platform_device* pdev; int /*<<< orphan*/  perf_lock; int /*<<< orphan*/  hangcheck_timer; int /*<<< orphan*/  recover_work; int /*<<< orphan*/  retire_work; int /*<<< orphan*/  active_list; struct msm_gpu_funcs const* funcs; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  DBG (char*,void*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  DRM_DEV_INFO (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  DRM_DEV_INFO_ONCE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MSM_BO_UNCACHED ; 
 int PTR_ERR (void*) ; 
 scalar_t__ WARN_ON (int) ; 
 void* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct msm_gpu*) ; 
 int get_clocks (struct platform_device*,struct msm_gpu*) ; 
 int /*<<< orphan*/  hangcheck_handler ; 
 int /*<<< orphan*/  irq_handler ; 
 void* msm_clk_get (struct platform_device*,char*) ; 
 int /*<<< orphan*/  msm_devfreq_init (struct msm_gpu*) ; 
 void* msm_gem_kernel_new (struct drm_device*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  msm_gem_kernel_put (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  msm_gem_object_set_name (int /*<<< orphan*/ ,char*) ; 
 void* msm_gpu_create_address_space (struct msm_gpu*,struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* msm_ioremap (struct platform_device*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  msm_ringbuffer_destroy (void*) ; 
 void* msm_ringbuffer_new (struct msm_gpu*,int,void*,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct msm_gpu*) ; 
 int /*<<< orphan*/  recover_worker ; 
 int /*<<< orphan*/  retire_worker ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int msm_gpu_init(struct drm_device *drm, struct platform_device *pdev,
		struct msm_gpu *gpu, const struct msm_gpu_funcs *funcs,
		const char *name, struct msm_gpu_config *config)
{
	int i, ret, nr_rings = config->nr_rings;
	void *memptrs;
	uint64_t memptrs_iova;

	if (WARN_ON(gpu->num_perfcntrs > ARRAY_SIZE(gpu->last_cntrs)))
		gpu->num_perfcntrs = ARRAY_SIZE(gpu->last_cntrs);

	gpu->dev = drm;
	gpu->funcs = funcs;
	gpu->name = name;

	INIT_LIST_HEAD(&gpu->active_list);
	INIT_WORK(&gpu->retire_work, retire_worker);
	INIT_WORK(&gpu->recover_work, recover_worker);


	timer_setup(&gpu->hangcheck_timer, hangcheck_handler, 0);

	spin_lock_init(&gpu->perf_lock);


	/* Map registers: */
	gpu->mmio = msm_ioremap(pdev, config->ioname, name);
	if (IS_ERR(gpu->mmio)) {
		ret = PTR_ERR(gpu->mmio);
		goto fail;
	}

	/* Get Interrupt: */
	gpu->irq = platform_get_irq(pdev, 0);
	if (gpu->irq < 0) {
		ret = gpu->irq;
		DRM_DEV_ERROR(drm->dev, "failed to get irq: %d\n", ret);
		goto fail;
	}

	ret = devm_request_irq(&pdev->dev, gpu->irq, irq_handler,
			IRQF_TRIGGER_HIGH, gpu->name, gpu);
	if (ret) {
		DRM_DEV_ERROR(drm->dev, "failed to request IRQ%u: %d\n", gpu->irq, ret);
		goto fail;
	}

	ret = get_clocks(pdev, gpu);
	if (ret)
		goto fail;

	gpu->ebi1_clk = msm_clk_get(pdev, "bus");
	DBG("ebi1_clk: %p", gpu->ebi1_clk);
	if (IS_ERR(gpu->ebi1_clk))
		gpu->ebi1_clk = NULL;

	/* Acquire regulators: */
	gpu->gpu_reg = devm_regulator_get(&pdev->dev, "vdd");
	DBG("gpu_reg: %p", gpu->gpu_reg);
	if (IS_ERR(gpu->gpu_reg))
		gpu->gpu_reg = NULL;

	gpu->gpu_cx = devm_regulator_get(&pdev->dev, "vddcx");
	DBG("gpu_cx: %p", gpu->gpu_cx);
	if (IS_ERR(gpu->gpu_cx))
		gpu->gpu_cx = NULL;

	gpu->pdev = pdev;
	platform_set_drvdata(pdev, gpu);

	msm_devfreq_init(gpu);

	gpu->aspace = msm_gpu_create_address_space(gpu, pdev,
		config->va_start, config->va_end);

	if (gpu->aspace == NULL)
		DRM_DEV_INFO(drm->dev, "%s: no IOMMU, fallback to VRAM carveout!\n", name);
	else if (IS_ERR(gpu->aspace)) {
		ret = PTR_ERR(gpu->aspace);
		goto fail;
	}

	memptrs = msm_gem_kernel_new(drm,
		sizeof(struct msm_rbmemptrs) * nr_rings,
		MSM_BO_UNCACHED, gpu->aspace, &gpu->memptrs_bo,
		&memptrs_iova);

	if (IS_ERR(memptrs)) {
		ret = PTR_ERR(memptrs);
		DRM_DEV_ERROR(drm->dev, "could not allocate memptrs: %d\n", ret);
		goto fail;
	}

	msm_gem_object_set_name(gpu->memptrs_bo, "memptrs");

	if (nr_rings > ARRAY_SIZE(gpu->rb)) {
		DRM_DEV_INFO_ONCE(drm->dev, "Only creating %zu ringbuffers\n",
			ARRAY_SIZE(gpu->rb));
		nr_rings = ARRAY_SIZE(gpu->rb);
	}

	/* Create ringbuffer(s): */
	for (i = 0; i < nr_rings; i++) {
		gpu->rb[i] = msm_ringbuffer_new(gpu, i, memptrs, memptrs_iova);

		if (IS_ERR(gpu->rb[i])) {
			ret = PTR_ERR(gpu->rb[i]);
			DRM_DEV_ERROR(drm->dev,
				"could not create ringbuffer %d: %d\n", i, ret);
			goto fail;
		}

		memptrs += sizeof(struct msm_rbmemptrs);
		memptrs_iova += sizeof(struct msm_rbmemptrs);
	}

	gpu->nr_rings = nr_rings;

	return 0;

fail:
	for (i = 0; i < ARRAY_SIZE(gpu->rb); i++)  {
		msm_ringbuffer_destroy(gpu->rb[i]);
		gpu->rb[i] = NULL;
	}

	msm_gem_kernel_put(gpu->memptrs_bo, gpu->aspace, false);

	platform_set_drvdata(pdev, NULL);
	return ret;
}