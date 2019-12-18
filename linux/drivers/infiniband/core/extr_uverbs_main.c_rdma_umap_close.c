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
struct vm_area_struct {struct rdma_umap_priv* vm_private_data; TYPE_1__* vm_file; } ;
struct rdma_umap_priv {int /*<<< orphan*/  list; } ;
struct ib_uverbs_file {int /*<<< orphan*/  umap_lock; } ;
struct TYPE_2__ {struct ib_uverbs_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rdma_umap_priv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rdma_umap_close(struct vm_area_struct *vma)
{
	struct ib_uverbs_file *ufile = vma->vm_file->private_data;
	struct rdma_umap_priv *priv = vma->vm_private_data;

	if (!priv)
		return;

	/*
	 * The vma holds a reference on the struct file that created it, which
	 * in turn means that the ib_uverbs_file is guaranteed to exist at
	 * this point.
	 */
	mutex_lock(&ufile->umap_lock);
	list_del(&priv->list);
	mutex_unlock(&ufile->umap_lock);
	kfree(priv);
}