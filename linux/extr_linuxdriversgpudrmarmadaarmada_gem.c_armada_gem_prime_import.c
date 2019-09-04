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
struct drm_gem_object {struct dma_buf_attachment* import_attach; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dma_buf_attachment {int dummy; } ;
struct dma_buf {int /*<<< orphan*/  size; struct drm_gem_object* priv; int /*<<< orphan*/ * ops; } ;
struct armada_gem_object {struct drm_gem_object obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_gem_object* ERR_CAST (struct dma_buf_attachment*) ; 
 struct drm_gem_object* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dma_buf_attachment*) ; 
 struct armada_gem_object* armada_gem_alloc_private_object (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armada_gem_prime_dmabuf_ops ; 
 struct dma_buf_attachment* dma_buf_attach (struct dma_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_detach (struct dma_buf*,struct dma_buf_attachment*) ; 
 int /*<<< orphan*/  drm_gem_object_get (struct drm_gem_object*) ; 
 int /*<<< orphan*/  get_dma_buf (struct dma_buf*) ; 

struct drm_gem_object *
armada_gem_prime_import(struct drm_device *dev, struct dma_buf *buf)
{
	struct dma_buf_attachment *attach;
	struct armada_gem_object *dobj;

	if (buf->ops == &armada_gem_prime_dmabuf_ops) {
		struct drm_gem_object *obj = buf->priv;
		if (obj->dev == dev) {
			/*
			 * Importing our own dmabuf(s) increases the
			 * refcount on the gem object itself.
			 */
			drm_gem_object_get(obj);
			return obj;
		}
	}

	attach = dma_buf_attach(buf, dev->dev);
	if (IS_ERR(attach))
		return ERR_CAST(attach);

	dobj = armada_gem_alloc_private_object(dev, buf->size);
	if (!dobj) {
		dma_buf_detach(buf, attach);
		return ERR_PTR(-ENOMEM);
	}

	dobj->obj.import_attach = attach;
	get_dma_buf(buf);

	/*
	 * Don't call dma_buf_map_attachment() here - it maps the
	 * scatterlist immediately for DMA, and this is not always
	 * an appropriate thing to do.
	 */
	return &dobj->obj;
}