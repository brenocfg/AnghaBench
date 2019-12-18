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
struct sg_table {struct sg_table* import_attach; struct drm_device* dev; } ;
struct drm_gem_object {struct drm_gem_object* import_attach; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dma_buf_attachment {struct dma_buf_attachment* import_attach; struct drm_device* dev; } ;
struct dma_buf {int /*<<< orphan*/  size; struct sg_table* priv; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct sg_table* ERR_CAST (struct sg_table*) ; 
 struct sg_table* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 int PTR_ERR (struct sg_table*) ; 
 struct sg_table* dma_buf_attach (struct dma_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_detach (struct dma_buf*,struct sg_table*) ; 
 struct sg_table* dma_buf_map_attachment (struct sg_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (struct sg_table*,struct sg_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_get (struct sg_table*) ; 
 int /*<<< orphan*/  get_dma_buf (struct dma_buf*) ; 
 int /*<<< orphan*/  omap_dmabuf_ops ; 
 struct sg_table* omap_gem_new_dmabuf (struct drm_device*,int /*<<< orphan*/ ,struct sg_table*) ; 

struct drm_gem_object *omap_gem_prime_import(struct drm_device *dev,
					     struct dma_buf *dma_buf)
{
	struct dma_buf_attachment *attach;
	struct drm_gem_object *obj;
	struct sg_table *sgt;
	int ret;

	if (dma_buf->ops == &omap_dmabuf_ops) {
		obj = dma_buf->priv;
		if (obj->dev == dev) {
			/*
			 * Importing dmabuf exported from out own gem increases
			 * refcount on gem itself instead of f_count of dmabuf.
			 */
			drm_gem_object_get(obj);
			return obj;
		}
	}

	attach = dma_buf_attach(dma_buf, dev->dev);
	if (IS_ERR(attach))
		return ERR_CAST(attach);

	get_dma_buf(dma_buf);

	sgt = dma_buf_map_attachment(attach, DMA_TO_DEVICE);
	if (IS_ERR(sgt)) {
		ret = PTR_ERR(sgt);
		goto fail_detach;
	}

	obj = omap_gem_new_dmabuf(dev, dma_buf->size, sgt);
	if (IS_ERR(obj)) {
		ret = PTR_ERR(obj);
		goto fail_unmap;
	}

	obj->import_attach = attach;

	return obj;

fail_unmap:
	dma_buf_unmap_attachment(attach, sgt, DMA_TO_DEVICE);
fail_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);

	return ERR_PTR(ret);
}