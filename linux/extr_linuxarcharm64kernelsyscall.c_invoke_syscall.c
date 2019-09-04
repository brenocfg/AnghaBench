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
typedef  int /*<<< orphan*/  syscall_fn_t ;
struct pt_regs {long* regs; } ;

/* Variables and functions */
 long __invoke_syscall (struct pt_regs*,int /*<<< orphan*/ ) ; 
 size_t array_index_nospec (unsigned int,unsigned int) ; 
 long do_ni_syscall (struct pt_regs*,unsigned int) ; 

__attribute__((used)) static void invoke_syscall(struct pt_regs *regs, unsigned int scno,
			   unsigned int sc_nr,
			   const syscall_fn_t syscall_table[])
{
	long ret;

	if (scno < sc_nr) {
		syscall_fn_t syscall_fn;
		syscall_fn = syscall_table[array_index_nospec(scno, sc_nr)];
		ret = __invoke_syscall(regs, syscall_fn);
	} else {
		ret = do_ni_syscall(regs, scno);
	}

	regs->regs[0] = ret;
}