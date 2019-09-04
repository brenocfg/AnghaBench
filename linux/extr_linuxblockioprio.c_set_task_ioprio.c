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
struct task_struct {int dummy; } ;
struct io_context {int ioprio; } ;
struct cred {int /*<<< orphan*/  uid; int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 struct cred* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 struct io_context* get_task_io_context (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_io_context (struct io_context*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_task_setioprio (struct task_struct*,int) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int set_task_ioprio(struct task_struct *task, int ioprio)
{
	int err;
	struct io_context *ioc;
	const struct cred *cred = current_cred(), *tcred;

	rcu_read_lock();
	tcred = __task_cred(task);
	if (!uid_eq(tcred->uid, cred->euid) &&
	    !uid_eq(tcred->uid, cred->uid) && !capable(CAP_SYS_NICE)) {
		rcu_read_unlock();
		return -EPERM;
	}
	rcu_read_unlock();

	err = security_task_setioprio(task, ioprio);
	if (err)
		return err;

	ioc = get_task_io_context(task, GFP_ATOMIC, NUMA_NO_NODE);
	if (ioc) {
		ioc->ioprio = ioprio;
		put_io_context(ioc);
	}

	return err;
}