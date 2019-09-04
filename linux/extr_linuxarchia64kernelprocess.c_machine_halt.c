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
 int /*<<< orphan*/  DIE_MACHINE_HALT ; 
 int /*<<< orphan*/  cpu_halt () ; 
 int /*<<< orphan*/  notify_die (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
machine_halt (void)
{
	(void) notify_die(DIE_MACHINE_HALT, "", NULL, 0, 0, 0);
	cpu_halt();
}