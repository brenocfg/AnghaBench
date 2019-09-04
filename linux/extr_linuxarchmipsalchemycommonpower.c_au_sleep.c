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
#define  ALCHEMY_CPU_AU1000 133 
#define  ALCHEMY_CPU_AU1100 132 
#define  ALCHEMY_CPU_AU1200 131 
#define  ALCHEMY_CPU_AU1300 130 
#define  ALCHEMY_CPU_AU1500 129 
#define  ALCHEMY_CPU_AU1550 128 
 int alchemy_get_cputype () ; 
 int /*<<< orphan*/  alchemy_sleep_au1000 () ; 
 int /*<<< orphan*/  alchemy_sleep_au1300 () ; 
 int /*<<< orphan*/  alchemy_sleep_au1550 () ; 
 int /*<<< orphan*/  restore_core_regs () ; 
 int /*<<< orphan*/  save_core_regs () ; 

void au_sleep(void)
{
	save_core_regs();

	switch (alchemy_get_cputype()) {
	case ALCHEMY_CPU_AU1000:
	case ALCHEMY_CPU_AU1500:
	case ALCHEMY_CPU_AU1100:
		alchemy_sleep_au1000();
		break;
	case ALCHEMY_CPU_AU1550:
	case ALCHEMY_CPU_AU1200:
		alchemy_sleep_au1550();
		break;
	case ALCHEMY_CPU_AU1300:
		alchemy_sleep_au1300();
		break;
	}

	restore_core_regs();
}