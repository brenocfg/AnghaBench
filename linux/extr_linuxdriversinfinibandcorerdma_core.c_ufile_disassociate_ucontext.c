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
struct task_struct {scalar_t__ state; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct ib_ucontext {int /*<<< orphan*/  tgid; struct ib_device* device; } ;
struct ib_device {int /*<<< orphan*/  (* disassociate_ucontext ) (struct ib_ucontext*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 scalar_t__ TASK_DEAD ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct task_struct* get_pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  stub1 (struct ib_ucontext*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ufile_disassociate_ucontext(struct ib_ucontext *ibcontext)
{
	struct ib_device *ib_dev = ibcontext->device;
	struct task_struct *owning_process  = NULL;
	struct mm_struct   *owning_mm       = NULL;

	owning_process = get_pid_task(ibcontext->tgid, PIDTYPE_PID);
	if (!owning_process)
		return;

	owning_mm = get_task_mm(owning_process);
	if (!owning_mm) {
		pr_info("no mm, disassociate ucontext is pending task termination\n");
		while (1) {
			put_task_struct(owning_process);
			usleep_range(1000, 2000);
			owning_process = get_pid_task(ibcontext->tgid,
						      PIDTYPE_PID);
			if (!owning_process ||
			    owning_process->state == TASK_DEAD) {
				pr_info("disassociate ucontext done, task was terminated\n");
				/* in case task was dead need to release the
				 * task struct.
				 */
				if (owning_process)
					put_task_struct(owning_process);
				return;
			}
		}
	}

	down_write(&owning_mm->mmap_sem);
	ib_dev->disassociate_ucontext(ibcontext);
	up_write(&owning_mm->mmap_sem);
	mmput(owning_mm);
	put_task_struct(owning_process);
}