#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_object {struct dma_buf* dma_buf; } ;
struct drm_device {TYPE_1__* driver; } ;
struct dma_buf {int dummy; } ;
struct TYPE_2__ {struct dma_buf* (* gem_prime_export ) (struct drm_device*,struct drm_gem_object*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 int PTR_ERR (struct dma_buf*) ; 
 struct dma_buf* stub1 (struct drm_device*,struct drm_gem_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int attach_dmabuf(struct drm_device *dev,
			 struct drm_gem_object *obj)
{
	struct dma_buf *dmabuf;

	if (obj->dma_buf)
		return 0;

	dmabuf = dev->driver->gem_prime_export(dev, obj, 0);
	if (IS_ERR(dmabuf))
		return PTR_ERR(dmabuf);

	obj->dma_buf = dmabuf;
	return 0;
}