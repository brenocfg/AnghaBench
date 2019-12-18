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
struct srpt_ioctx {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
struct srpt_device {int /*<<< orphan*/  device; } ;
struct kmem_cache {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct srpt_ioctx*) ; 
 int /*<<< orphan*/  kmem_cache_alloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_size (struct kmem_cache*) ; 
 struct srpt_ioctx* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct srpt_ioctx *srpt_alloc_ioctx(struct srpt_device *sdev,
					   int ioctx_size,
					   struct kmem_cache *buf_cache,
					   enum dma_data_direction dir)
{
	struct srpt_ioctx *ioctx;

	ioctx = kzalloc(ioctx_size, GFP_KERNEL);
	if (!ioctx)
		goto err;

	ioctx->buf = kmem_cache_alloc(buf_cache, GFP_KERNEL);
	if (!ioctx->buf)
		goto err_free_ioctx;

	ioctx->dma = ib_dma_map_single(sdev->device, ioctx->buf,
				       kmem_cache_size(buf_cache), dir);
	if (ib_dma_mapping_error(sdev->device, ioctx->dma))
		goto err_free_buf;

	return ioctx;

err_free_buf:
	kmem_cache_free(buf_cache, ioctx->buf);
err_free_ioctx:
	kfree(ioctx);
err:
	return NULL;
}