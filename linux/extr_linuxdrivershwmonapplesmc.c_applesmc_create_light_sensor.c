#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  num_light_sensors; } ;

/* Variables and functions */
 int applesmc_create_nodes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  light_sensor_group ; 
 TYPE_1__ smcreg ; 

__attribute__((used)) static int applesmc_create_light_sensor(void)
{
	if (!smcreg.num_light_sensors)
		return 0;
	return applesmc_create_nodes(light_sensor_group, 1);
}