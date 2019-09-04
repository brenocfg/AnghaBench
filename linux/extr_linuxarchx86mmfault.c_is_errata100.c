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

__attribute__((used)) static int is_errata100(struct pt_regs *regs, unsigned long address)
{
#ifdef CONFIG_X86_64
	if ((regs->cs == __USER32_CS || (regs->cs & (1<<2))) && (address >> 32))
		return 1;
#endif
	return 0;
}