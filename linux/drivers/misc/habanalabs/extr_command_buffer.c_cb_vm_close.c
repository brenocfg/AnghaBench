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
struct vm_area_struct {long vm_end; long vm_start; int /*<<< orphan*/ * vm_private_data; } ;
struct hl_cb {long mmap_size; int mmap; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hl_cb_put (struct hl_cb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cb_vm_close(struct vm_area_struct *vma)
{
	struct hl_cb *cb = (struct hl_cb *) vma->vm_private_data;
	long new_mmap_size;

	new_mmap_size = cb->mmap_size - (vma->vm_end - vma->vm_start);

	if (new_mmap_size > 0) {
		cb->mmap_size = new_mmap_size;
		return;
	}

	spin_lock(&cb->lock);
	cb->mmap = false;
	spin_unlock(&cb->lock);

	hl_cb_put(cb);
	vma->vm_private_data = NULL;
}