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
struct platform_device {int dummy; } ;
struct msm_gpu {int /*<<< orphan*/  aspace; int /*<<< orphan*/  num_perfcntrs; int /*<<< orphan*/  perfcntrs; } ;
struct msm_drm_private {struct platform_device* gpu_pdev; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct adreno_gpu {struct msm_gpu base; int /*<<< orphan*/  reg_offsets; int /*<<< orphan*/  registers; } ;
struct a2xx_gpu {struct adreno_gpu base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENXIO ; 
 struct msm_gpu* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  a200_registers ; 
 int /*<<< orphan*/  a220_registers ; 
 int /*<<< orphan*/  a225_registers ; 
 int /*<<< orphan*/  a2xx_destroy (struct msm_gpu*) ; 
 int /*<<< orphan*/  a2xx_register_offsets ; 
 int adreno_gpu_init (struct drm_device*,struct platform_device*,struct adreno_gpu*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ adreno_is_a20x (struct adreno_gpu*) ; 
 scalar_t__ adreno_is_a225 (struct adreno_gpu*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  funcs ; 
 struct a2xx_gpu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perfcntrs ; 

struct msm_gpu *a2xx_gpu_init(struct drm_device *dev)
{
	struct a2xx_gpu *a2xx_gpu = NULL;
	struct adreno_gpu *adreno_gpu;
	struct msm_gpu *gpu;
	struct msm_drm_private *priv = dev->dev_private;
	struct platform_device *pdev = priv->gpu_pdev;
	int ret;

	if (!pdev) {
		dev_err(dev->dev, "no a2xx device\n");
		ret = -ENXIO;
		goto fail;
	}

	a2xx_gpu = kzalloc(sizeof(*a2xx_gpu), GFP_KERNEL);
	if (!a2xx_gpu) {
		ret = -ENOMEM;
		goto fail;
	}

	adreno_gpu = &a2xx_gpu->base;
	gpu = &adreno_gpu->base;

	gpu->perfcntrs = perfcntrs;
	gpu->num_perfcntrs = ARRAY_SIZE(perfcntrs);

	if (adreno_is_a20x(adreno_gpu))
		adreno_gpu->registers = a200_registers;
	else if (adreno_is_a225(adreno_gpu))
		adreno_gpu->registers = a225_registers;
	else
		adreno_gpu->registers = a220_registers;

	adreno_gpu->reg_offsets = a2xx_register_offsets;

	ret = adreno_gpu_init(dev, pdev, adreno_gpu, &funcs, 1);
	if (ret)
		goto fail;

	if (!gpu->aspace) {
		dev_err(dev->dev, "No memory protection without MMU\n");
		ret = -ENXIO;
		goto fail;
	}

	return gpu;

fail:
	if (a2xx_gpu)
		a2xx_destroy(&a2xx_gpu->base.base);

	return ERR_PTR(ret);
}