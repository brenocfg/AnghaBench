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
struct vb2_dma_sg_buf {int dma_sgt; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  db_attach; } ;
struct sg_table {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct sg_table* dma_buf_map_attachment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int vb2_dma_sg_map_dmabuf(void *mem_priv)
{
	struct vb2_dma_sg_buf *buf = mem_priv;
	struct sg_table *sgt;

	if (WARN_ON(!buf->db_attach)) {
		pr_err("trying to pin a non attached buffer\n");
		return -EINVAL;
	}

	if (WARN_ON(buf->dma_sgt)) {
		pr_err("dmabuf buffer is already pinned\n");
		return 0;
	}

	/* get the associated scatterlist for this buffer */
	sgt = dma_buf_map_attachment(buf->db_attach, buf->dma_dir);
	if (IS_ERR(sgt)) {
		pr_err("Error getting dmabuf scatterlist\n");
		return -EINVAL;
	}

	buf->dma_sgt = sgt;
	buf->vaddr = NULL;

	return 0;
}