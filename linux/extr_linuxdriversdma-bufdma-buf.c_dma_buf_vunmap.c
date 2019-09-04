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
struct dma_buf {void* vmap_ptr; scalar_t__ vmapping_counter; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* vunmap ) (struct dma_buf*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dma_buf*,void*) ; 

void dma_buf_vunmap(struct dma_buf *dmabuf, void *vaddr)
{
	if (WARN_ON(!dmabuf))
		return;

	BUG_ON(!dmabuf->vmap_ptr);
	BUG_ON(dmabuf->vmapping_counter == 0);
	BUG_ON(dmabuf->vmap_ptr != vaddr);

	mutex_lock(&dmabuf->lock);
	if (--dmabuf->vmapping_counter == 0) {
		if (dmabuf->ops->vunmap)
			dmabuf->ops->vunmap(dmabuf, vaddr);
		dmabuf->vmap_ptr = NULL;
	}
	mutex_unlock(&dmabuf->lock);
}