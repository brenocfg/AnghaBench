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

void check_bugs(void)
{
#if defined(CONFIG_FPU) && !defined(CONFIG_M68KFPU_EMU)
	if (m68k_fputype == 0) {
		pr_emerg("*** YOU DO NOT HAVE A FLOATING POINT UNIT, "
			"WHICH IS REQUIRED BY LINUX/M68K ***\n");
		pr_emerg("Upgrade your hardware or join the FPU "
			"emulation project\n");
		panic("no FPU");
	}
#endif /* !CONFIG_M68KFPU_EMU */
}