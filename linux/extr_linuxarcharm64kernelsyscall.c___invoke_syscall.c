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
typedef  long (* syscall_fn_t ) (struct pt_regs*) ;
struct pt_regs {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static long __invoke_syscall(struct pt_regs *regs, syscall_fn_t syscall_fn)
{
	return syscall_fn(regs);
}