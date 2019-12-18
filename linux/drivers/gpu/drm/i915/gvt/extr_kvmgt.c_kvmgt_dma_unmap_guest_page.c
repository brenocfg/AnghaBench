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
struct kvmgt_guest_info {TYPE_2__* vgpu; } ;
struct gvt_dma {int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  cache_lock; } ;
struct TYPE_4__ {TYPE_1__ vdev; } ;

/* Variables and functions */
 struct gvt_dma* __gvt_cache_find_dma_addr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __gvt_dma_release ; 
 int /*<<< orphan*/  handle_valid (unsigned long) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmgt_dma_unmap_guest_page(unsigned long handle, dma_addr_t dma_addr)
{
	struct kvmgt_guest_info *info;
	struct gvt_dma *entry;

	if (!handle_valid(handle))
		return;

	info = (struct kvmgt_guest_info *)handle;

	mutex_lock(&info->vgpu->vdev.cache_lock);
	entry = __gvt_cache_find_dma_addr(info->vgpu, dma_addr);
	if (entry)
		kref_put(&entry->ref, __gvt_dma_release);
	mutex_unlock(&info->vgpu->vdev.cache_lock);
}