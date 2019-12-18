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
struct fastrpc_dma_buf_attachment {int /*<<< orphan*/  node; int /*<<< orphan*/  dev; int /*<<< orphan*/  sgt; } ;
struct fastrpc_buf {int /*<<< orphan*/  lock; int /*<<< orphan*/  attachments; int /*<<< orphan*/  dev; int /*<<< orphan*/  size; int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct dma_buf_attachment {struct fastrpc_dma_buf_attachment* priv; int /*<<< orphan*/  dev; } ;
struct dma_buf {struct fastrpc_buf* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FASTRPC_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dma_get_sgtable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fastrpc_dma_buf_attachment*) ; 
 struct fastrpc_dma_buf_attachment* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fastrpc_dma_buf_attach(struct dma_buf *dmabuf,
				  struct dma_buf_attachment *attachment)
{
	struct fastrpc_dma_buf_attachment *a;
	struct fastrpc_buf *buffer = dmabuf->priv;
	int ret;

	a = kzalloc(sizeof(*a), GFP_KERNEL);
	if (!a)
		return -ENOMEM;

	ret = dma_get_sgtable(buffer->dev, &a->sgt, buffer->virt,
			      FASTRPC_PHYS(buffer->phys), buffer->size);
	if (ret < 0) {
		dev_err(buffer->dev, "failed to get scatterlist from DMA API\n");
		kfree(a);
		return -EINVAL;
	}

	a->dev = attachment->dev;
	INIT_LIST_HEAD(&a->node);
	attachment->priv = a;

	mutex_lock(&buffer->lock);
	list_add(&a->node, &buffer->attachments);
	mutex_unlock(&buffer->lock);

	return 0;
}