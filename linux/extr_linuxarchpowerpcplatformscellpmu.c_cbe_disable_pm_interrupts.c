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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cbe_get_and_clear_pm_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbe_write_pm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_status ; 

void cbe_disable_pm_interrupts(u32 cpu)
{
	cbe_get_and_clear_pm_interrupts(cpu);
	cbe_write_pm(cpu, pm_status, 0);
}