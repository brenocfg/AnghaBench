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
struct zone_device {int dummy; } ;

/* Variables and functions */
 int max_id ; 
 int topology_logical_die_id (unsigned int) ; 
 struct zone_device** zones ; 

__attribute__((used)) static struct zone_device *pkg_temp_thermal_get_dev(unsigned int cpu)
{
	int id = topology_logical_die_id(cpu);

	if (id >= 0 && id < max_id)
		return zones[id];
	return NULL;
}