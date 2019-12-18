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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {unsigned long pgoff; struct page* page; TYPE_2__* vma; } ;
struct page {int dummy; } ;
struct mon_reader_bin {unsigned long b_size; int /*<<< orphan*/  fetch_lock; TYPE_1__* b_vec; } ;
struct TYPE_4__ {struct mon_reader_bin* vm_private_data; } ;
struct TYPE_3__ {struct page* pg; } ;

/* Variables and functions */
 unsigned long CHUNK_SIZE ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_fault_t mon_bin_vma_fault(struct vm_fault *vmf)
{
	struct mon_reader_bin *rp = vmf->vma->vm_private_data;
	unsigned long offset, chunk_idx;
	struct page *pageptr;

	mutex_lock(&rp->fetch_lock);
	offset = vmf->pgoff << PAGE_SHIFT;
	if (offset >= rp->b_size) {
		mutex_unlock(&rp->fetch_lock);
		return VM_FAULT_SIGBUS;
	}
	chunk_idx = offset / CHUNK_SIZE;
	pageptr = rp->b_vec[chunk_idx].pg;
	get_page(pageptr);
	mutex_unlock(&rp->fetch_lock);
	vmf->page = pageptr;
	return 0;
}