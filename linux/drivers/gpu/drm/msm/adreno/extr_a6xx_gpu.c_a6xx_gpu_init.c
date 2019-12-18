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
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct msm_gpu {TYPE_2__* aspace; } ;
struct msm_drm_private {struct platform_device* gpu_pdev; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct device_node {int dummy; } ;
struct adreno_gpu {struct msm_gpu base; int /*<<< orphan*/  reg_offsets; int /*<<< orphan*/ * registers; } ;
struct a6xx_gpu {struct adreno_gpu base; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct msm_gpu* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  a6xx_destroy (struct msm_gpu*) ; 
 int /*<<< orphan*/  a6xx_fault_handler ; 
 int a6xx_gmu_init (struct a6xx_gpu*,struct device_node*) ; 
 int /*<<< orphan*/  a6xx_register_offsets ; 
 int adreno_gpu_init (struct drm_device*,struct platform_device*,struct adreno_gpu*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  funcs ; 
 struct a6xx_gpu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_mmu_set_fault_handler (int /*<<< orphan*/ ,struct msm_gpu*,int /*<<< orphan*/ ) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct msm_gpu *a6xx_gpu_init(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct platform_device *pdev = priv->gpu_pdev;
	struct device_node *node;
	struct a6xx_gpu *a6xx_gpu;
	struct adreno_gpu *adreno_gpu;
	struct msm_gpu *gpu;
	int ret;

	a6xx_gpu = kzalloc(sizeof(*a6xx_gpu), GFP_KERNEL);
	if (!a6xx_gpu)
		return ERR_PTR(-ENOMEM);

	adreno_gpu = &a6xx_gpu->base;
	gpu = &adreno_gpu->base;

	adreno_gpu->registers = NULL;
	adreno_gpu->reg_offsets = a6xx_register_offsets;

	ret = adreno_gpu_init(dev, pdev, adreno_gpu, &funcs, 1);
	if (ret) {
		a6xx_destroy(&(a6xx_gpu->base.base));
		return ERR_PTR(ret);
	}

	/* Check if there is a GMU phandle and set it up */
	node = of_parse_phandle(pdev->dev.of_node, "qcom,gmu", 0);

	/* FIXME: How do we gracefully handle this? */
	BUG_ON(!node);

	ret = a6xx_gmu_init(a6xx_gpu, node);
	if (ret) {
		a6xx_destroy(&(a6xx_gpu->base.base));
		return ERR_PTR(ret);
	}

	if (gpu->aspace)
		msm_mmu_set_fault_handler(gpu->aspace->mmu, gpu,
				a6xx_fault_handler);

	return gpu;
}