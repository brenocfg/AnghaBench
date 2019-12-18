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
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct drm_vma_entry {int /*<<< orphan*/  head; int /*<<< orphan*/  pid; struct vm_area_struct* vma; } ;
struct drm_device {int /*<<< orphan*/  vmalist; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* current ; 
 struct drm_vma_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_vm_open_locked(struct drm_device *dev,
			       struct vm_area_struct *vma)
{
	struct drm_vma_entry *vma_entry;

	DRM_DEBUG("0x%08lx,0x%08lx\n",
		  vma->vm_start, vma->vm_end - vma->vm_start);

	vma_entry = kmalloc(sizeof(*vma_entry), GFP_KERNEL);
	if (vma_entry) {
		vma_entry->vma = vma;
		vma_entry->pid = current->pid;
		list_add(&vma_entry->head, &dev->vmalist);
	}
}