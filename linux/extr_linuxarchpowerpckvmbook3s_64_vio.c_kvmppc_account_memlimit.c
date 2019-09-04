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
struct TYPE_4__ {TYPE_1__* mm; int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {unsigned long locked_vm; int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 long ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char,unsigned long,unsigned long,unsigned long,char*) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long kvmppc_account_memlimit(unsigned long stt_pages, bool inc)
{
	long ret = 0;

	if (!current || !current->mm)
		return ret; /* process exited */

	down_write(&current->mm->mmap_sem);

	if (inc) {
		unsigned long locked, lock_limit;

		locked = current->mm->locked_vm + stt_pages;
		lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
		if (locked > lock_limit && !capable(CAP_IPC_LOCK))
			ret = -ENOMEM;
		else
			current->mm->locked_vm += stt_pages;
	} else {
		if (WARN_ON_ONCE(stt_pages > current->mm->locked_vm))
			stt_pages = current->mm->locked_vm;

		current->mm->locked_vm -= stt_pages;
	}

	pr_debug("[%d] RLIMIT_MEMLOCK KVM %c%ld %ld/%ld%s\n", current->pid,
			inc ? '+' : '-',
			stt_pages << PAGE_SHIFT,
			current->mm->locked_vm << PAGE_SHIFT,
			rlimit(RLIMIT_MEMLOCK),
			ret ? " - exceeded" : "");

	up_write(&current->mm->mmap_sem);

	return ret;
}