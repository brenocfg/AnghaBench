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
struct vm_area_struct {int vm_flags; struct privcmd_buf_vma_private* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct privcmd_buf_vma_private {unsigned long n_pages; int users; int /*<<< orphan*/ * pages; int /*<<< orphan*/  list; struct privcmd_buf_private* file_priv; } ;
struct privcmd_buf_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct file {struct privcmd_buf_private* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_SHARED ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  alloc_page (int) ; 
 struct privcmd_buf_vma_private* kzalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pages ; 
 int /*<<< orphan*/  privcmd_buf_vm_ops ; 
 int /*<<< orphan*/  privcmd_buf_vmapriv_free (struct privcmd_buf_vma_private*) ; 
 int /*<<< orphan*/  struct_size (struct privcmd_buf_vma_private*,int /*<<< orphan*/ ,unsigned long) ; 
 int vm_map_pages_zero (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static int privcmd_buf_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct privcmd_buf_private *file_priv = file->private_data;
	struct privcmd_buf_vma_private *vma_priv;
	unsigned long count = vma_pages(vma);
	unsigned int i;
	int ret = 0;

	if (!(vma->vm_flags & VM_SHARED))
		return -EINVAL;

	vma_priv = kzalloc(struct_size(vma_priv, pages, count), GFP_KERNEL);
	if (!vma_priv)
		return -ENOMEM;

	for (i = 0; i < count; i++) {
		vma_priv->pages[i] = alloc_page(GFP_KERNEL | __GFP_ZERO);
		if (!vma_priv->pages[i])
			break;
		vma_priv->n_pages++;
	}

	mutex_lock(&file_priv->lock);

	vma_priv->file_priv = file_priv;
	vma_priv->users = 1;

	vma->vm_flags |= VM_IO | VM_DONTEXPAND;
	vma->vm_ops = &privcmd_buf_vm_ops;
	vma->vm_private_data = vma_priv;

	list_add(&vma_priv->list, &file_priv->list);

	if (vma_priv->n_pages != count)
		ret = -ENOMEM;
	else
		ret = vm_map_pages_zero(vma, vma_priv->pages,
						vma_priv->n_pages);

	if (ret)
		privcmd_buf_vmapriv_free(vma_priv);

	mutex_unlock(&file_priv->lock);

	return ret;
}