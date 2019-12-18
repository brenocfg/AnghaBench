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
struct drm_vma_offset_manager {int /*<<< orphan*/  vm_addr_space_mm; int /*<<< orphan*/  vm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

void drm_vma_offset_manager_init(struct drm_vma_offset_manager *mgr,
				 unsigned long page_offset, unsigned long size)
{
	rwlock_init(&mgr->vm_lock);
	drm_mm_init(&mgr->vm_addr_space_mm, page_offset, size);
}