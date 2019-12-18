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
struct kfd_process {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 struct kfd_process* find_process_by_mm (struct mm_struct const*) ; 
 int /*<<< orphan*/  kfd_processes_srcu ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

struct kfd_process *kfd_lookup_process_by_mm(const struct mm_struct *mm)
{
	struct kfd_process *p;

	int idx = srcu_read_lock(&kfd_processes_srcu);

	p = find_process_by_mm(mm);
	if (p)
		kref_get(&p->ref);

	srcu_read_unlock(&kfd_processes_srcu, idx);

	return p;
}