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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 opti_syscfg(u8 reg)
{
	unsigned long flags;
	u8 r;

	/* Uniprocessor chipset and must force cycles adjancent */
	local_irq_save(flags);
	outb(reg, 0x22);
	r = inb(0x24);
	local_irq_restore(flags);
	return r;
}