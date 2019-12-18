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
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  root_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcm_loop_driverfs ; 
 int /*<<< orphan*/  tcm_loop_lld_bus ; 
 int /*<<< orphan*/  tcm_loop_primary ; 

__attribute__((used)) static void tcm_loop_release_core_bus(void)
{
	driver_unregister(&tcm_loop_driverfs);
	bus_unregister(&tcm_loop_lld_bus);
	root_device_unregister(tcm_loop_primary);

	pr_debug("Releasing TCM Loop Core BUS\n");
}