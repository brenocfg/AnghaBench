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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  pm_status ; 
 int /*<<< orphan*/  ps3_write_pm (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void ps3_enable_pm_interrupts(u32 cpu, u32 thread, u32 mask)
{
	if (mask)
		ps3_write_pm(cpu, pm_status, mask);
}