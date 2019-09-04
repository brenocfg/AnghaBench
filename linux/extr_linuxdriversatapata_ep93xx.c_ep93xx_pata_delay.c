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

__attribute__((used)) static void ep93xx_pata_delay(unsigned long count)
{
	__asm__ volatile (
		"0:\n"
		"mov r0, r0\n"
		"subs %0, %1, #1\n"
		"bge 0b\n"
		: "=r" (count)
		: "0" (count)
	);
}