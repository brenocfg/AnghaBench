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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline int _wakeupgen_get_irq_info(u32 irq, u32 *bit_posn, u8 *reg_index)
{
	/*
	 * Each WakeupGen register controls 32 interrupt.
	 * i.e. 1 bit per SPI IRQ
	 */
	*reg_index = irq >> 5;
	*bit_posn = irq %= 32;

	return 0;
}