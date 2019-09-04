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

/* Variables and functions */
 long ptrace_request (struct task_struct*,long,unsigned long,unsigned long) ; 

long arch_ptrace(struct task_struct *child, long request,
		 unsigned long addr, unsigned long data)
{
	return ptrace_request(child, request, addr, data);
}