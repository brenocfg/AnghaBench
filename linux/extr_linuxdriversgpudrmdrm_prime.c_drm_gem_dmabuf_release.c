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
struct drm_gem_object {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct dma_buf {struct drm_gem_object* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 

void drm_gem_dmabuf_release(struct dma_buf *dma_buf)
{
	struct drm_gem_object *obj = dma_buf->priv;
	struct drm_device *dev = obj->dev;

	/* drop the reference on the export fd holds */
	drm_gem_object_put_unlocked(obj);

	drm_dev_put(dev);
}