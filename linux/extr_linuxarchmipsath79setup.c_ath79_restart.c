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
 int /*<<< orphan*/  AR71XX_RESET_FULL_CHIP ; 
 int /*<<< orphan*/  ath79_device_reset_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_wait () ; 
 int /*<<< orphan*/  local_irq_disable () ; 

__attribute__((used)) static void ath79_restart(char *command)
{
	local_irq_disable();
	ath79_device_reset_set(AR71XX_RESET_FULL_CHIP);
	for (;;)
		if (cpu_wait)
			cpu_wait();
}