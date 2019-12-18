#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  paddr; } ;
struct vc4_bo {scalar_t__ madv; TYPE_2__ base; int /*<<< orphan*/  madv_lock; } ;
struct drm_gem_object {int /*<<< orphan*/  size; int /*<<< orphan*/  vma_node; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__* anon_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 scalar_t__ VC4_MADV_DONTNEED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __VC4_MADV_PURGED ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_vma_node_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 

__attribute__((used)) static void vc4_bo_purge(struct drm_gem_object *obj)
{
	struct vc4_bo *bo = to_vc4_bo(obj);
	struct drm_device *dev = obj->dev;

	WARN_ON(!mutex_is_locked(&bo->madv_lock));
	WARN_ON(bo->madv != VC4_MADV_DONTNEED);

	drm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);

	dma_free_wc(dev->dev, obj->size, bo->base.vaddr, bo->base.paddr);
	bo->base.vaddr = NULL;
	bo->madv = __VC4_MADV_PURGED;
}