#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_shmem_object {int madv; TYPE_3__* sgt; } ;
struct drm_gem_object {int /*<<< orphan*/  filp; int /*<<< orphan*/  vma_node; struct drm_device* dev; } ;
struct drm_device {TYPE_1__* anon_inode; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_8__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_free_mmap_offset (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_shmem_is_purgeable (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  drm_gem_shmem_put_pages_locked (struct drm_gem_shmem_object*) ; 
 int /*<<< orphan*/  drm_vma_node_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_3__*) ; 
 int /*<<< orphan*/  shmem_truncate_range (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_gem_shmem_object* to_drm_gem_shmem_obj (struct drm_gem_object*) ; 

void drm_gem_shmem_purge_locked(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	WARN_ON(!drm_gem_shmem_is_purgeable(shmem));

	dma_unmap_sg(obj->dev->dev, shmem->sgt->sgl,
		     shmem->sgt->nents, DMA_BIDIRECTIONAL);
	sg_free_table(shmem->sgt);
	kfree(shmem->sgt);
	shmem->sgt = NULL;

	drm_gem_shmem_put_pages_locked(shmem);

	shmem->madv = -1;

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
}