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
 scalar_t__* ni_device_routes_list ; 
 int /*<<< orphan*/  ni_sort_device_routes (scalar_t__) ; 

__attribute__((used)) static void ni_sort_all_device_routes(void)
{
	unsigned int i;

	for (i = 0; ni_device_routes_list[i]; ++i)
		ni_sort_device_routes(ni_device_routes_list[i]);
}