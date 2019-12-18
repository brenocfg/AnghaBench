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
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct fastrpc_dma_buf_attachment {struct sg_table sgt; } ;
struct dma_buf_attachment {int /*<<< orphan*/  dev; struct fastrpc_dma_buf_attachment* priv; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sg_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct sg_table *
fastrpc_map_dma_buf(struct dma_buf_attachment *attachment,
		    enum dma_data_direction dir)
{
	struct fastrpc_dma_buf_attachment *a = attachment->priv;
	struct sg_table *table;

	table = &a->sgt;

	if (!dma_map_sg(attachment->dev, table->sgl, table->nents, dir))
		return ERR_PTR(-ENOMEM);

	return table;
}