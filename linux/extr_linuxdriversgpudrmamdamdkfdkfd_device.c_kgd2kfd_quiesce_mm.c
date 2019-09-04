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
struct mm_struct {int dummy; } ;
struct kfd_process {int dummy; } ;

/* Variables and functions */
 int ESRCH ; 
 struct kfd_process* kfd_lookup_process_by_mm (struct mm_struct*) ; 
 int kfd_process_evict_queues (struct kfd_process*) ; 
 int /*<<< orphan*/  kfd_unref_process (struct kfd_process*) ; 

int kgd2kfd_quiesce_mm(struct mm_struct *mm)
{
	struct kfd_process *p;
	int r;

	/* Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to exit while we are
	 * running so the lookup function increments the process ref count.
	 */
	p = kfd_lookup_process_by_mm(mm);
	if (!p)
		return -ESRCH;

	r = kfd_process_evict_queues(p);

	kfd_unref_process(p);
	return r;
}