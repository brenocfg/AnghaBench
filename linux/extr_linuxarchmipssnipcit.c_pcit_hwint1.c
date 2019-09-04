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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IE_IRQ1 ; 
 scalar_t__ SNI_PCIT_INT_REG ; 
 scalar_t__ SNI_PCIT_INT_START ; 
 int /*<<< orphan*/  clear_c0_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 int ffs (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  set_c0_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcit_hwint1(void)
{
	u32 pending = *(volatile u32 *)SNI_PCIT_INT_REG;
	int irq;

	clear_c0_status(IE_IRQ1);
	irq = ffs((pending >> 16) & 0x7f);

	if (likely(irq > 0))
		do_IRQ(irq + SNI_PCIT_INT_START - 1);
	set_c0_status(IE_IRQ1);
}