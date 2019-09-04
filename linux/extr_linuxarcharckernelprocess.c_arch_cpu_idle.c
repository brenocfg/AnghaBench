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

void arch_cpu_idle(void)
{
	/* sleep, but enable both set E1/E2 (levels of interrutps) before committing */
	__asm__ __volatile__("sleep 0x3	\n");
}