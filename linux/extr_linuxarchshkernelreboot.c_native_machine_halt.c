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
 int /*<<< orphan*/  machine_shutdown () ; 
 int /*<<< orphan*/  stop_this_cpu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void native_machine_halt(void)
{
	/* stop other cpus */
	machine_shutdown();

	/* stop this cpu */
	stop_this_cpu(NULL);
}