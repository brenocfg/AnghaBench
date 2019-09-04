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
struct sg_table {int /*<<< orphan*/  nents; struct scatterlist* sgl; } ;
struct scatterlist {int dummy; } ;
struct mock_dmabuf {int npages; int /*<<< orphan*/ * pages; } ;
struct dma_buf_attachment {int /*<<< orphan*/  dev; int /*<<< orphan*/  dmabuf; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int ENOMEM ; 
 struct sg_table* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct sg_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int sg_alloc_table (struct sg_table*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mock_dmabuf* to_mock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sg_table *mock_map_dma_buf(struct dma_buf_attachment *attachment,
					 enum dma_data_direction dir)
{
	struct mock_dmabuf *mock = to_mock(attachment->dmabuf);
	struct sg_table *st;
	struct scatterlist *sg;
	int i, err;

	st = kmalloc(sizeof(*st), GFP_KERNEL);
	if (!st)
		return ERR_PTR(-ENOMEM);

	err = sg_alloc_table(st, mock->npages, GFP_KERNEL);
	if (err)
		goto err_free;

	sg = st->sgl;
	for (i = 0; i < mock->npages; i++) {
		sg_set_page(sg, mock->pages[i], PAGE_SIZE, 0);
		sg = sg_next(sg);
	}

	if (!dma_map_sg(attachment->dev, st->sgl, st->nents, dir)) {
		err = -ENOMEM;
		goto err_st;
	}

	return st;

err_st:
	sg_free_table(st);
err_free:
	kfree(st);
	return ERR_PTR(err);
}