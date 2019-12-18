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
struct kgd_mem {int /*<<< orphan*/  invalid; struct amdkfd_process_info* process_info; } ;
struct amdkfd_process_info {int /*<<< orphan*/  restore_userptr_work; int /*<<< orphan*/  evicted_bos; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_USERPTR_RESTORE_DELAY_MS ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int kgd2kfd_quiesce_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int amdgpu_amdkfd_evict_userptr(struct kgd_mem *mem,
				struct mm_struct *mm)
{
	struct amdkfd_process_info *process_info = mem->process_info;
	int invalid, evicted_bos;
	int r = 0;

	invalid = atomic_inc_return(&mem->invalid);
	evicted_bos = atomic_inc_return(&process_info->evicted_bos);
	if (evicted_bos == 1) {
		/* First eviction, stop the queues */
		r = kgd2kfd_quiesce_mm(mm);
		if (r)
			pr_err("Failed to quiesce KFD\n");
		schedule_delayed_work(&process_info->restore_userptr_work,
			msecs_to_jiffies(AMDGPU_USERPTR_RESTORE_DELAY_MS));
	}

	return r;
}