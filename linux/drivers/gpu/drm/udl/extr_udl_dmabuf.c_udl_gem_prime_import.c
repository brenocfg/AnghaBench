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
struct drm_gem_object {struct sg_table* import_attach; } ;
struct udl_gem_object {struct drm_gem_object base; int /*<<< orphan*/  flags; } ;
struct sg_table {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  struct sg_table dma_buf_attachment ;
struct dma_buf {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 struct drm_gem_object* ERR_CAST (struct sg_table*) ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 int PTR_ERR (struct sg_table*) ; 
 int /*<<< orphan*/  UDL_BO_WC ; 
 struct sg_table* dma_buf_attach (struct dma_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_detach (struct dma_buf*,struct sg_table*) ; 
 struct sg_table* dma_buf_map_attachment (struct sg_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (struct sg_table*,struct sg_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_buf (struct dma_buf*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int udl_prime_create (struct drm_device*,int /*<<< orphan*/ ,struct sg_table*,struct udl_gem_object**) ; 

struct drm_gem_object *udl_gem_prime_import(struct drm_device *dev,
				struct dma_buf *dma_buf)
{
	struct dma_buf_attachment *attach;
	struct sg_table *sg;
	struct udl_gem_object *uobj;
	int ret;

	/* need to attach */
	get_device(dev->dev);
	attach = dma_buf_attach(dma_buf, dev->dev);
	if (IS_ERR(attach)) {
		put_device(dev->dev);
		return ERR_CAST(attach);
	}

	get_dma_buf(dma_buf);

	sg = dma_buf_map_attachment(attach, DMA_BIDIRECTIONAL);
	if (IS_ERR(sg)) {
		ret = PTR_ERR(sg);
		goto fail_detach;
	}

	ret = udl_prime_create(dev, dma_buf->size, sg, &uobj);
	if (ret)
		goto fail_unmap;

	uobj->base.import_attach = attach;
	uobj->flags = UDL_BO_WC;

	return &uobj->base;

fail_unmap:
	dma_buf_unmap_attachment(attach, sg, DMA_BIDIRECTIONAL);
fail_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);
	put_device(dev->dev);
	return ERR_PTR(ret);
}