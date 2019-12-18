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
struct qmp {TYPE_1__* cooling_devs; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int QMP_NUM_COOLING_RESOURCES ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qmp_cooling_devices_remove(struct qmp *qmp)
{
	int i;

	for (i = 0; i < QMP_NUM_COOLING_RESOURCES; i++)
		thermal_cooling_device_unregister(qmp->cooling_devs[i].cdev);
}