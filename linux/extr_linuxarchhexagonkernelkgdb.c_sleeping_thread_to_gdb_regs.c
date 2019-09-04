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
struct pt_regs {unsigned long r00; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMREGBYTES ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs,
				 struct task_struct *task)
{
	struct pt_regs *thread_regs;

	if (task == NULL)
		return;

	/* Initialize to zero */
	memset(gdb_regs, 0, NUMREGBYTES);

	/* Otherwise, we have only some registers from switch_to() */
	thread_regs = task_pt_regs(task);
	gdb_regs[0] = thread_regs->r00;
}