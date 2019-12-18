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
struct drm_gem_object {int /*<<< orphan*/  resv; struct dma_buf_attachment* import_attach; struct drm_device* dev; } ;
struct drm_i915_gem_object {struct drm_gem_object base; scalar_t__ write_domain; int /*<<< orphan*/  read_domains; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dma_buf_attachment {int dummy; } ;
struct dma_buf {int /*<<< orphan*/  resv; int /*<<< orphan*/  size; int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {struct drm_gem_object base; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_gem_object* ERR_CAST (struct dma_buf_attachment*) ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  I915_GEM_DOMAIN_GTT ; 
 scalar_t__ IS_ERR (struct dma_buf_attachment*) ; 
 struct dma_buf_attachment* dma_buf_attach (struct dma_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_detach (struct dma_buf*,struct dma_buf_attachment*) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 struct drm_i915_gem_object* dma_buf_to_obj (struct dma_buf*) ; 
 int /*<<< orphan*/  drm_gem_private_object_init (struct drm_device*,struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_buf (struct dma_buf*) ; 
 int /*<<< orphan*/  i915_dmabuf_ops ; 
 struct drm_i915_gem_object* i915_gem_object_alloc () ; 
 int /*<<< orphan*/  i915_gem_object_dmabuf_ops ; 
 TYPE_1__* i915_gem_object_get (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_init (struct drm_i915_gem_object*,int /*<<< orphan*/ *) ; 

struct drm_gem_object *i915_gem_prime_import(struct drm_device *dev,
					     struct dma_buf *dma_buf)
{
	struct dma_buf_attachment *attach;
	struct drm_i915_gem_object *obj;
	int ret;

	/* is this one of own objects? */
	if (dma_buf->ops == &i915_dmabuf_ops) {
		obj = dma_buf_to_obj(dma_buf);
		/* is it from our device? */
		if (obj->base.dev == dev) {
			/*
			 * Importing dmabuf exported from out own gem increases
			 * refcount on gem itself instead of f_count of dmabuf.
			 */
			return &i915_gem_object_get(obj)->base;
		}
	}

	/* need to attach */
	attach = dma_buf_attach(dma_buf, dev->dev);
	if (IS_ERR(attach))
		return ERR_CAST(attach);

	get_dma_buf(dma_buf);

	obj = i915_gem_object_alloc();
	if (obj == NULL) {
		ret = -ENOMEM;
		goto fail_detach;
	}

	drm_gem_private_object_init(dev, &obj->base, dma_buf->size);
	i915_gem_object_init(obj, &i915_gem_object_dmabuf_ops);
	obj->base.import_attach = attach;
	obj->base.resv = dma_buf->resv;

	/* We use GTT as shorthand for a coherent domain, one that is
	 * neither in the GPU cache nor in the CPU cache, where all
	 * writes are immediately visible in memory. (That's not strictly
	 * true, but it's close! There are internal buffers such as the
	 * write-combined buffer or a delay through the chipset for GTT
	 * writes that do require us to treat GTT as a separate cache domain.)
	 */
	obj->read_domains = I915_GEM_DOMAIN_GTT;
	obj->write_domain = 0;

	return &obj->base;

fail_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);

	return ERR_PTR(ret);
}