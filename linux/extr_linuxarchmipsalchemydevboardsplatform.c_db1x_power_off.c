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
 int /*<<< orphan*/  BCSR_RESETS ; 
 int /*<<< orphan*/  BCSR_SYSTEM ; 
 int BCSR_SYSTEM_PWROFF ; 
 int BCSR_SYSTEM_RESET ; 
 int /*<<< orphan*/  bcsr_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_wait () ; 

__attribute__((used)) static void db1x_power_off(void)
{
	bcsr_write(BCSR_RESETS, 0);
	bcsr_write(BCSR_SYSTEM, BCSR_SYSTEM_PWROFF | BCSR_SYSTEM_RESET);
	while (1)		/* sit and spin */
		cpu_wait();
}