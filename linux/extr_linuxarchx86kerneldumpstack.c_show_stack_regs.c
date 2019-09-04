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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEFAULT ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  show_trace_log_lvl (int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void show_stack_regs(struct pt_regs *regs)
{
	show_trace_log_lvl(current, regs, NULL, KERN_DEFAULT);
}