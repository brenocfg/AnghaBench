#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct arch_uprobe {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* emulate ) (struct arch_uprobe*,struct pt_regs*) ;} ;

/* Variables and functions */
 int stub1 (struct arch_uprobe*,struct pt_regs*) ; 

__attribute__((used)) static bool __skip_sstep(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	if (auprobe->ops->emulate)
		return auprobe->ops->emulate(auprobe, regs);
	return false;
}