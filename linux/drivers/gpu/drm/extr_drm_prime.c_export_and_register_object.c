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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_gem_object {scalar_t__ handle_count; struct dma_buf* dma_buf; TYPE_2__* funcs; } ;
struct drm_device {TYPE_1__* driver; } ;
struct dma_buf {int dummy; } ;
struct TYPE_4__ {struct dma_buf* (* export ) (struct drm_gem_object*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct dma_buf* (* gem_prime_export ) (struct drm_gem_object*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dma_buf* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 struct dma_buf* drm_gem_prime_export (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_buf (struct dma_buf*) ; 
 struct dma_buf* stub1 (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 struct dma_buf* stub2 (struct drm_gem_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dma_buf *export_and_register_object(struct drm_device *dev,
						  struct drm_gem_object *obj,
						  uint32_t flags)
{
	struct dma_buf *dmabuf;

	/* prevent races with concurrent gem_close. */
	if (obj->handle_count == 0) {
		dmabuf = ERR_PTR(-ENOENT);
		return dmabuf;
	}

	if (obj->funcs && obj->funcs->export)
		dmabuf = obj->funcs->export(obj, flags);
	else if (dev->driver->gem_prime_export)
		dmabuf = dev->driver->gem_prime_export(obj, flags);
	else
		dmabuf = drm_gem_prime_export(obj, flags);
	if (IS_ERR(dmabuf)) {
		/* normally the created dma-buf takes ownership of the ref,
		 * but if that fails then drop the ref
		 */
		return dmabuf;
	}

	/*
	 * Note that callers do not need to clean up the export cache
	 * since the check for obj->handle_count guarantees that someone
	 * will clean it up.
	 */
	obj->dma_buf = dmabuf;
	get_dma_buf(obj->dma_buf);

	return dmabuf;
}