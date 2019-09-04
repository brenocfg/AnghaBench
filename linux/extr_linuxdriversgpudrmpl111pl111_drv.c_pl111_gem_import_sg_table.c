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
struct sg_table {int dummy; } ;
struct pl111_drm_dev_private {scalar_t__ use_device_memory; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {struct pl111_drm_dev_private* dev_private; } ;
struct dma_buf_attachment {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct drm_gem_object* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct drm_gem_object* drm_gem_cma_prime_import_sg_table (struct drm_device*,struct dma_buf_attachment*,struct sg_table*) ; 

__attribute__((used)) static struct drm_gem_object *
pl111_gem_import_sg_table(struct drm_device *dev,
			  struct dma_buf_attachment *attach,
			  struct sg_table *sgt)
{
	struct pl111_drm_dev_private *priv = dev->dev_private;

	/*
	 * When using device-specific reserved memory we can't import
	 * DMA buffers: those are passed by reference in any global
	 * memory and we can only handle a specific range of memory.
	 */
	if (priv->use_device_memory)
		return ERR_PTR(-EINVAL);

	return drm_gem_cma_prime_import_sg_table(dev, attach, sgt);
}