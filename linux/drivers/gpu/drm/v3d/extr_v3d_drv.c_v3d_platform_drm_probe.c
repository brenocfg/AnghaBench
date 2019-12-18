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
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {struct v3d_dev* dev_private; } ;
struct v3d_dev {int va_width; int ver; int cores; int /*<<< orphan*/  mmu_scratch_paddr; int /*<<< orphan*/  mmu_scratch; struct drm_device drm; int /*<<< orphan*/  gca_regs; int /*<<< orphan*/  bridge_regs; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * core_regs; int /*<<< orphan*/  hub_regs; struct platform_device* pdev; struct device* dev; } ;
struct device {int /*<<< orphan*/  coherent_dma_mask; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int V3D_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_HUB_IDENT1 ; 
 int /*<<< orphan*/  V3D_HUB_IDENT1_NCORES ; 
 int /*<<< orphan*/  V3D_HUB_IDENT1_REV ; 
 int /*<<< orphan*/  V3D_HUB_IDENT1_TVER ; 
 int /*<<< orphan*/  V3D_MMU_DEBUG_INFO ; 
 int /*<<< orphan*/  V3D_MMU_PA_WIDTH ; 
 int /*<<< orphan*/  V3D_MMU_VA_WIDTH ; 
 int /*<<< orphan*/  V3D_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_reset_control_get_exclusive (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_alloc_wc (struct device*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_free_wc (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_dev_init (struct drm_device*,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct v3d_dev*) ; 
 struct v3d_dev* kzalloc (int,int) ; 
 int map_regs (struct v3d_dev*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct drm_device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  v3d_drm_driver ; 
 int /*<<< orphan*/  v3d_gem_destroy (struct drm_device*) ; 
 int v3d_gem_init (struct drm_device*) ; 
 int /*<<< orphan*/  v3d_irq_disable (struct v3d_dev*) ; 
 int v3d_irq_init (struct v3d_dev*) ; 

__attribute__((used)) static int v3d_platform_drm_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct drm_device *drm;
	struct v3d_dev *v3d;
	int ret;
	u32 mmu_debug;
	u32 ident1;


	v3d = kzalloc(sizeof(*v3d), GFP_KERNEL);
	if (!v3d)
		return -ENOMEM;
	v3d->dev = dev;
	v3d->pdev = pdev;
	drm = &v3d->drm;

	ret = map_regs(v3d, &v3d->hub_regs, "hub");
	if (ret)
		goto dev_free;

	ret = map_regs(v3d, &v3d->core_regs[0], "core0");
	if (ret)
		goto dev_free;

	mmu_debug = V3D_READ(V3D_MMU_DEBUG_INFO);
	dev->coherent_dma_mask =
		DMA_BIT_MASK(30 + V3D_GET_FIELD(mmu_debug, V3D_MMU_PA_WIDTH));
	v3d->va_width = 30 + V3D_GET_FIELD(mmu_debug, V3D_MMU_VA_WIDTH);

	ident1 = V3D_READ(V3D_HUB_IDENT1);
	v3d->ver = (V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_TVER) * 10 +
		    V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_REV));
	v3d->cores = V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_NCORES);
	WARN_ON(v3d->cores > 1); /* multicore not yet implemented */

	v3d->reset = devm_reset_control_get_exclusive(dev, NULL);
	if (IS_ERR(v3d->reset)) {
		ret = PTR_ERR(v3d->reset);

		if (ret == -EPROBE_DEFER)
			goto dev_free;

		v3d->reset = NULL;
		ret = map_regs(v3d, &v3d->bridge_regs, "bridge");
		if (ret) {
			dev_err(dev,
				"Failed to get reset control or bridge regs\n");
			goto dev_free;
		}
	}

	if (v3d->ver < 41) {
		ret = map_regs(v3d, &v3d->gca_regs, "gca");
		if (ret)
			goto dev_free;
	}

	v3d->mmu_scratch = dma_alloc_wc(dev, 4096, &v3d->mmu_scratch_paddr,
					GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO);
	if (!v3d->mmu_scratch) {
		dev_err(dev, "Failed to allocate MMU scratch page\n");
		ret = -ENOMEM;
		goto dev_free;
	}

	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, 50);
	pm_runtime_enable(dev);

	ret = drm_dev_init(&v3d->drm, &v3d_drm_driver, dev);
	if (ret)
		goto dma_free;

	platform_set_drvdata(pdev, drm);
	drm->dev_private = v3d;

	ret = v3d_gem_init(drm);
	if (ret)
		goto dev_destroy;

	ret = v3d_irq_init(v3d);
	if (ret)
		goto gem_destroy;

	ret = drm_dev_register(drm, 0);
	if (ret)
		goto irq_disable;

	return 0;

irq_disable:
	v3d_irq_disable(v3d);
gem_destroy:
	v3d_gem_destroy(drm);
dev_destroy:
	drm_dev_put(drm);
dma_free:
	dma_free_wc(dev, 4096, v3d->mmu_scratch, v3d->mmu_scratch_paddr);
dev_free:
	kfree(v3d);
	return ret;
}