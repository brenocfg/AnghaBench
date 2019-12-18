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
struct mtk_drm_private {int /*<<< orphan*/  dma_dev; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {struct mtk_drm_private* dev_private; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 struct drm_gem_object* drm_gem_prime_import_dev (struct drm_device*,struct dma_buf*,int /*<<< orphan*/ ) ; 

struct drm_gem_object *mtk_drm_gem_prime_import(struct drm_device *dev,
						struct dma_buf *dma_buf)
{
	struct mtk_drm_private *private = dev->dev_private;

	return drm_gem_prime_import_dev(dev, dma_buf, private->dma_dev);
}