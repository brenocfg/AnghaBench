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
struct arch_uprobe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  riprel_pre_xol (struct arch_uprobe*,struct pt_regs*) ; 

__attribute__((used)) static int default_pre_xol_op(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	riprel_pre_xol(auprobe, regs);
	return 0;
}