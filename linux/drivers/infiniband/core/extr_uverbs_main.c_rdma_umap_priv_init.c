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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; struct rdma_umap_priv* vm_private_data; TYPE_1__* vm_file; } ;
struct rdma_umap_priv {int /*<<< orphan*/  list; struct vm_area_struct* vma; } ;
struct ib_uverbs_file {int /*<<< orphan*/  umap_lock; int /*<<< orphan*/  umaps; } ;
struct TYPE_2__ {struct ib_uverbs_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_umap_ops ; 

__attribute__((used)) static void rdma_umap_priv_init(struct rdma_umap_priv *priv,
				struct vm_area_struct *vma)
{
	struct ib_uverbs_file *ufile = vma->vm_file->private_data;

	priv->vma = vma;
	vma->vm_private_data = priv;
	vma->vm_ops = &rdma_umap_ops;

	mutex_lock(&ufile->umap_lock);
	list_add(&priv->list, &ufile->umaps);
	mutex_unlock(&ufile->umap_lock);
}