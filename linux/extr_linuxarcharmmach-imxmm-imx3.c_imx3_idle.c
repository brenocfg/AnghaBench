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

/* Variables and functions */

__attribute__((used)) static void imx3_idle(void)
{
	unsigned long reg = 0;

	__asm__ __volatile__(
		/* disable I and D cache */
		"mrc p15, 0, %0, c1, c0, 0\n"
		"bic %0, %0, #0x00001000\n"
		"bic %0, %0, #0x00000004\n"
		"mcr p15, 0, %0, c1, c0, 0\n"
		/* invalidate I cache */
		"mov %0, #0\n"
		"mcr p15, 0, %0, c7, c5, 0\n"
		/* clear and invalidate D cache */
		"mov %0, #0\n"
		"mcr p15, 0, %0, c7, c14, 0\n"
		/* WFI */
		"mov %0, #0\n"
		"mcr p15, 0, %0, c7, c0, 4\n"
		"nop\n" "nop\n" "nop\n" "nop\n"
		"nop\n" "nop\n" "nop\n"
		/* enable I and D cache */
		"mrc p15, 0, %0, c1, c0, 0\n"
		"orr %0, %0, #0x00001000\n"
		"orr %0, %0, #0x00000004\n"
		"mcr p15, 0, %0, c1, c0, 0\n"
		: "=r" (reg));
}