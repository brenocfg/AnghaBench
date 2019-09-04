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
struct usnic_uiom_reg {unsigned long diff; int /*<<< orphan*/  work; struct mm_struct* mm; scalar_t__ offset; scalar_t__ length; int /*<<< orphan*/  pd; } ;
struct task_struct {int dummy; } ;
struct mm_struct {unsigned long pinned_vm; int /*<<< orphan*/  mmap_sem; } ;
struct ib_ucontext {scalar_t__ closing; int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long PAGE_ALIGN (scalar_t__) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  __usnic_uiom_reg_release (int /*<<< orphan*/ ,struct usnic_uiom_reg*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write_trylock (int /*<<< orphan*/ *) ; 
 struct task_struct* get_pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  kfree (struct usnic_uiom_reg*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_uiom_reg_account ; 
 int /*<<< orphan*/  usnic_uiom_wq ; 

void usnic_uiom_reg_release(struct usnic_uiom_reg *uiomr,
			    struct ib_ucontext *ucontext)
{
	struct task_struct *task;
	struct mm_struct *mm;
	unsigned long diff;

	__usnic_uiom_reg_release(uiomr->pd, uiomr, 1);

	task = get_pid_task(ucontext->tgid, PIDTYPE_PID);
	if (!task)
		goto out;
	mm = get_task_mm(task);
	put_task_struct(task);
	if (!mm)
		goto out;

	diff = PAGE_ALIGN(uiomr->length + uiomr->offset) >> PAGE_SHIFT;

	/*
	 * We may be called with the mm's mmap_sem already held.  This
	 * can happen when a userspace munmap() is the call that drops
	 * the last reference to our file and calls our release
	 * method.  If there are memory regions to destroy, we'll end
	 * up here and not be able to take the mmap_sem.  In that case
	 * we defer the vm_locked accounting to the system workqueue.
	 */
	if (ucontext->closing) {
		if (!down_write_trylock(&mm->mmap_sem)) {
			INIT_WORK(&uiomr->work, usnic_uiom_reg_account);
			uiomr->mm = mm;
			uiomr->diff = diff;

			queue_work(usnic_uiom_wq, &uiomr->work);
			return;
		}
	} else
		down_write(&mm->mmap_sem);

	mm->pinned_vm -= diff;
	up_write(&mm->mmap_sem);
	mmput(mm);
out:
	kfree(uiomr);
}