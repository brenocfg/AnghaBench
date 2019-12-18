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
struct vm_area_struct {struct gntdev_grant_map* vm_private_data; struct file* vm_file; } ;
struct gntdev_priv {int /*<<< orphan*/  lock; } ;
struct gntdev_grant_map {int /*<<< orphan*/ * vma; } ;
struct file {struct gntdev_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gntdev_put_map (struct gntdev_priv*,struct gntdev_grant_map*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct vm_area_struct*) ; 
 scalar_t__ use_ptemod ; 

__attribute__((used)) static void gntdev_vma_close(struct vm_area_struct *vma)
{
	struct gntdev_grant_map *map = vma->vm_private_data;
	struct file *file = vma->vm_file;
	struct gntdev_priv *priv = file->private_data;

	pr_debug("gntdev_vma_close %p\n", vma);
	if (use_ptemod) {
		/* It is possible that an mmu notifier could be running
		 * concurrently, so take priv->lock to ensure that the vma won't
		 * vanishing during the unmap_grant_pages call, since we will
		 * spin here until that completes. Such a concurrent call will
		 * not do any unmapping, since that has been done prior to
		 * closing the vma, but it may still iterate the unmap_ops list.
		 */
		mutex_lock(&priv->lock);
		map->vma = NULL;
		mutex_unlock(&priv->lock);
	}
	vma->vm_private_data = NULL;
	gntdev_put_map(priv, map);
}