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
struct drm_gem_object {int /*<<< orphan*/  resv; int /*<<< orphan*/  size; struct drm_device* dev; } ;
struct drm_device {TYPE_2__* driver; } ;
struct dma_buf_export_info {int flags; int /*<<< orphan*/  resv; struct drm_gem_object* priv; int /*<<< orphan*/  size; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; int /*<<< orphan*/  exp_name; } ;
struct dma_buf {int dummy; } ;
struct TYPE_4__ {TYPE_1__* fops; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 struct dma_buf* drm_gem_dmabuf_export (struct drm_device*,struct dma_buf_export_info*) ; 
 int /*<<< orphan*/  drm_gem_prime_dmabuf_ops ; 

struct dma_buf *drm_gem_prime_export(struct drm_gem_object *obj,
				     int flags)
{
	struct drm_device *dev = obj->dev;
	struct dma_buf_export_info exp_info = {
		.exp_name = KBUILD_MODNAME, /* white lie for debug */
		.owner = dev->driver->fops->owner,
		.ops = &drm_gem_prime_dmabuf_ops,
		.size = obj->size,
		.flags = flags,
		.priv = obj,
		.resv = obj->resv,
	};

	return drm_gem_dmabuf_export(dev, &exp_info);
}