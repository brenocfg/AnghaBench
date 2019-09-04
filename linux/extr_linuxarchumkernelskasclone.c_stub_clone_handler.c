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
struct stub_data {long err; int /*<<< orphan*/  offset; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int CLONE_FILES ; 
 int CLONE_PARENT ; 
 int /*<<< orphan*/  PTRACE_TRACEME ; 
 int SIGCHLD ; 
 int STUB_DATA ; 
 int UM_KERN_PAGE_SIZE ; 
 int /*<<< orphan*/  __NR_clone ; 
 int /*<<< orphan*/  __NR_ptrace ; 
 int /*<<< orphan*/  remap_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long stub_syscall2 (int /*<<< orphan*/ ,int,int) ; 
 long stub_syscall4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_myself () ; 

void __attribute__ ((__section__ (".__syscall_stub")))
stub_clone_handler(void)
{
	struct stub_data *data = (struct stub_data *) STUB_DATA;
	long err;

	err = stub_syscall2(__NR_clone, CLONE_PARENT | CLONE_FILES | SIGCHLD,
			    STUB_DATA + UM_KERN_PAGE_SIZE / 2 - sizeof(void *));
	if (err != 0)
		goto out;

	err = stub_syscall4(__NR_ptrace, PTRACE_TRACEME, 0, 0, 0);
	if (err)
		goto out;

	remap_stack(data->fd, data->offset);
	goto done;

 out:
	/*
	 * save current result.
	 * Parent: pid;
	 * child: retcode of mmap already saved and it jumps around this
	 * assignment
	 */
	data->err = err;
 done:
	trap_myself();
}