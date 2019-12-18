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
struct fastrpc_dma_buf_attachment {int /*<<< orphan*/  sgt; int /*<<< orphan*/  node; } ;
struct fastrpc_buf {int /*<<< orphan*/  lock; } ;
struct dma_buf_attachment {struct fastrpc_dma_buf_attachment* priv; } ;
struct dma_buf {struct fastrpc_buf* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fastrpc_dma_buf_attachment*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fastrpc_dma_buf_detatch(struct dma_buf *dmabuf,
				    struct dma_buf_attachment *attachment)
{
	struct fastrpc_dma_buf_attachment *a = attachment->priv;
	struct fastrpc_buf *buffer = dmabuf->priv;

	mutex_lock(&buffer->lock);
	list_del(&a->node);
	mutex_unlock(&buffer->lock);
	sg_free_table(&a->sgt);
	kfree(a);
}