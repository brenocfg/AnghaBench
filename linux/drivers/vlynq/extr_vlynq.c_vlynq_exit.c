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
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlynq_bus_type ; 
 int /*<<< orphan*/  vlynq_platform_driver ; 

__attribute__((used)) static void vlynq_exit(void)
{
	platform_driver_unregister(&vlynq_platform_driver);
	bus_unregister(&vlynq_bus_type);
}