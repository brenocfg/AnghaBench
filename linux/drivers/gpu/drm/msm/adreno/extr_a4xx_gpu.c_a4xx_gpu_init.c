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
struct ocmem_buf {int len; int /*<<< orphan*/  addr; } ;
struct msm_gpu {int /*<<< orphan*/  aspace; scalar_t__ num_perfcntrs; int /*<<< orphan*/ * perfcntrs; } ;
struct msm_drm_private {struct platform_device* gpu_pdev; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct adreno_gpu {int gmem; struct msm_gpu base; int /*<<< orphan*/  reg_offsets; int /*<<< orphan*/  registers; } ;
struct a4xx_gpu {struct adreno_gpu base; int /*<<< orphan*/  ocmem_base; struct ocmem_buf* ocmem_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 struct msm_gpu* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OCMEM_GRAPHICS ; 
 int /*<<< orphan*/  a4xx_destroy (struct msm_gpu*) ; 
 int /*<<< orphan*/  a4xx_register_offsets ; 
 int /*<<< orphan*/  a4xx_registers ; 
 int adreno_gpu_init (struct drm_device*,struct platform_device*,struct adreno_gpu*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ adreno_is_a4xx (struct adreno_gpu*) ; 
 int /*<<< orphan*/  funcs ; 
 struct a4xx_gpu* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ocmem_buf* ocmem_allocate (int /*<<< orphan*/ ,int) ; 

struct msm_gpu *a4xx_gpu_init(struct drm_device *dev)
{
	struct a4xx_gpu *a4xx_gpu = NULL;
	struct adreno_gpu *adreno_gpu;
	struct msm_gpu *gpu;
	struct msm_drm_private *priv = dev->dev_private;
	struct platform_device *pdev = priv->gpu_pdev;
	int ret;

	if (!pdev) {
		DRM_DEV_ERROR(dev->dev, "no a4xx device\n");
		ret = -ENXIO;
		goto fail;
	}

	a4xx_gpu = kzalloc(sizeof(*a4xx_gpu), GFP_KERNEL);
	if (!a4xx_gpu) {
		ret = -ENOMEM;
		goto fail;
	}

	adreno_gpu = &a4xx_gpu->base;
	gpu = &adreno_gpu->base;

	gpu->perfcntrs = NULL;
	gpu->num_perfcntrs = 0;

	adreno_gpu->registers = a4xx_registers;
	adreno_gpu->reg_offsets = a4xx_register_offsets;

	ret = adreno_gpu_init(dev, pdev, adreno_gpu, &funcs, 1);
	if (ret)
		goto fail;

	/* if needed, allocate gmem: */
	if (adreno_is_a4xx(adreno_gpu)) {
#ifdef CONFIG_MSM_OCMEM
		/* TODO this is different/missing upstream: */
		struct ocmem_buf *ocmem_hdl =
				ocmem_allocate(OCMEM_GRAPHICS, adreno_gpu->gmem);

		a4xx_gpu->ocmem_hdl = ocmem_hdl;
		a4xx_gpu->ocmem_base = ocmem_hdl->addr;
		adreno_gpu->gmem = ocmem_hdl->len;
		DBG("using %dK of OCMEM at 0x%08x", adreno_gpu->gmem / 1024,
				a4xx_gpu->ocmem_base);
#endif
	}

	if (!gpu->aspace) {
		/* TODO we think it is possible to configure the GPU to
		 * restrict access to VRAM carveout.  But the required
		 * registers are unknown.  For now just bail out and
		 * limp along with just modesetting.  If it turns out
		 * to not be possible to restrict access, then we must
		 * implement a cmdstream validator.
		 */
		DRM_DEV_ERROR(dev->dev, "No memory protection without IOMMU\n");
		ret = -ENXIO;
		goto fail;
	}

	return gpu;

fail:
	if (a4xx_gpu)
		a4xx_destroy(&a4xx_gpu->base.base);

	return ERR_PTR(ret);
}