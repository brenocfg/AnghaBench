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
 int /*<<< orphan*/  show_regs_print_info (int /*<<< orphan*/ ) ; 

void show_regs(struct pt_regs *regs)
{
	extern void show_registers(struct pt_regs *regs);

	show_regs_print_info(KERN_DEFAULT);
	/* __PHX__ cleanup this mess */
	show_registers(regs);
}