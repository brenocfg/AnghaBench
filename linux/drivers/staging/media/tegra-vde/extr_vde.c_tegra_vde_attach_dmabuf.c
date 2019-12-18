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
typedef  size_t u64 ;
struct TYPE_2__ {struct device* parent; } ;
struct tegra_vde {TYPE_1__ miscdev; } ;
struct dma_buf_attachment {int dummy; } ;
struct dma_buf {size_t size; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 int PTR_ERR (struct dma_buf*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct dma_buf* dma_buf_get (int) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int tegra_vde_dmabuf_cache_map (struct tegra_vde*,struct dma_buf*,int,struct dma_buf_attachment**,scalar_t__*) ; 

__attribute__((used)) static int tegra_vde_attach_dmabuf(struct tegra_vde *vde,
				   int fd,
				   unsigned long offset,
				   size_t min_size,
				   size_t align_size,
				   struct dma_buf_attachment **a,
				   dma_addr_t *addrp,
				   size_t *size,
				   enum dma_data_direction dma_dir)
{
	struct device *dev = vde->miscdev.parent;
	struct dma_buf *dmabuf;
	int err;

	dmabuf = dma_buf_get(fd);
	if (IS_ERR(dmabuf)) {
		dev_err(dev, "Invalid dmabuf FD\n");
		return PTR_ERR(dmabuf);
	}

	if (dmabuf->size & (align_size - 1)) {
		dev_err(dev, "Unaligned dmabuf 0x%zX, should be aligned to 0x%zX\n",
			dmabuf->size, align_size);
		return -EINVAL;
	}

	if ((u64)offset + min_size > dmabuf->size) {
		dev_err(dev, "Too small dmabuf size %zu @0x%lX, should be at least %zu\n",
			dmabuf->size, offset, min_size);
		return -EINVAL;
	}

	err = tegra_vde_dmabuf_cache_map(vde, dmabuf, dma_dir, a, addrp);
	if (err)
		goto err_put;

	*addrp = *addrp + offset;

	if (size)
		*size = dmabuf->size - offset;

	return 0;

err_put:
	dma_buf_put(dmabuf);

	return err;
}