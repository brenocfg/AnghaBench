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
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {long locked_vm; int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int ENOMEM ; 
 long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,char,long,long,long,char*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 long rlimit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afu_dma_adjust_locked_vm(struct device *dev, long npages, bool incr)
{
	unsigned long locked, lock_limit;
	int ret = 0;

	/* the task is exiting. */
	if (!current->mm)
		return 0;

	down_write(&current->mm->mmap_sem);

	if (incr) {
		locked = current->mm->locked_vm + npages;
		lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;

		if (locked > lock_limit && !capable(CAP_IPC_LOCK))
			ret = -ENOMEM;
		else
			current->mm->locked_vm += npages;
	} else {
		if (WARN_ON_ONCE(npages > current->mm->locked_vm))
			npages = current->mm->locked_vm;
		current->mm->locked_vm -= npages;
	}

	dev_dbg(dev, "[%d] RLIMIT_MEMLOCK %c%ld %ld/%ld%s\n", current->pid,
		incr ? '+' : '-', npages << PAGE_SHIFT,
		current->mm->locked_vm << PAGE_SHIFT, rlimit(RLIMIT_MEMLOCK),
		ret ? "- execeeded" : "");

	up_write(&current->mm->mmap_sem);

	return ret;
}