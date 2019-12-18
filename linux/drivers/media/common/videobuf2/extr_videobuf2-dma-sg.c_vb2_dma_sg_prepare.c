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
struct vb2_dma_sg_buf {int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  dev; scalar_t__ db_attach; struct sg_table* dma_sgt; } ;
struct sg_table {int /*<<< orphan*/  orig_nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_sync_sg_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vb2_dma_sg_prepare(void *buf_priv)
{
	struct vb2_dma_sg_buf *buf = buf_priv;
	struct sg_table *sgt = buf->dma_sgt;

	/* DMABUF exporter will flush the cache for us */
	if (buf->db_attach)
		return;

	dma_sync_sg_for_device(buf->dev, sgt->sgl, sgt->orig_nents,
			       buf->dma_dir);
}