#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_gem_object {int /*<<< orphan*/  lock; int /*<<< orphan*/  madv; } ;
struct drm_gem_object {int import_attach; int /*<<< orphan*/  filp; int /*<<< orphan*/  vma_node; struct drm_device* dev; } ;
struct drm_device {TYPE_1__* anon_inode; int /*<<< orphan*/  struct_mutex; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  enum msm_gem_lock { ____Placeholder_msm_gem_lock } msm_gem_lock ;
struct TYPE_5__ {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __MSM_MADV_PURGED ; 
 int /*<<< orphan*/  drm_gem_free_mmap_offset (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_vma_node_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_purgeable (struct msm_gem_object*) ; 
 int /*<<< orphan*/  msm_gem_vunmap_locked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_iova (struct drm_gem_object*) ; 
 int /*<<< orphan*/  put_pages (struct drm_gem_object*) ; 
 int /*<<< orphan*/  shmem_truncate_range (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

void msm_gem_purge(struct drm_gem_object *obj, enum msm_gem_lock subclass)
{
	struct drm_device *dev = obj->dev;
	struct msm_gem_object *msm_obj = to_msm_bo(obj);

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));
	WARN_ON(!is_purgeable(msm_obj));
	WARN_ON(obj->import_attach);

	mutex_lock_nested(&msm_obj->lock, subclass);

	put_iova(obj);

	msm_gem_vunmap_locked(obj);

	put_pages(obj);

	msm_obj->madv = __MSM_MADV_PURGED;

	drm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);
	drm_gem_free_mmap_offset(obj);

	/* Our goal here is to return as much of the memory as
	 * is possible back to the system as we are called from OOM.
	 * To do this we must instruct the shmfs to drop all of its
	 * backing pages, *now*.
	 */
	shmem_truncate_range(file_inode(obj->filp), 0, (loff_t)-1);

	invalidate_mapping_pages(file_inode(obj->filp)->i_mapping,
			0, (loff_t)-1);

	mutex_unlock(&msm_obj->lock);
}