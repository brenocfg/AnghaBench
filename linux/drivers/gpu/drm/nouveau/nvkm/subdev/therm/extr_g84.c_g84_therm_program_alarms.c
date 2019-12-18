#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  alarm_program_lock; } ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct TYPE_10__ {int hysteresis; int temp; } ;
struct TYPE_9__ {int temp; int /*<<< orphan*/  hysteresis; } ;
struct TYPE_8__ {int temp; int /*<<< orphan*/  hysteresis; } ;
struct TYPE_7__ {int temp; int /*<<< orphan*/  hysteresis; } ;
struct nvbios_therm_sensor {TYPE_5__ thrs_shutdown; TYPE_4__ thrs_critical; TYPE_3__ thrs_down_clock; TYPE_2__ thrs_fan_boost; } ;
struct nvkm_therm {TYPE_1__ sensor; struct nvkm_subdev subdev; struct nvbios_therm_sensor bios_sensor; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
g84_therm_program_alarms(struct nvkm_therm *therm)
{
	struct nvbios_therm_sensor *sensor = &therm->bios_sensor;
	struct nvkm_subdev *subdev = &therm->subdev;
	struct nvkm_device *device = subdev->device;
	unsigned long flags;

	spin_lock_irqsave(&therm->sensor.alarm_program_lock, flags);

	/* enable RISING and FALLING IRQs for shutdown, THRS 0, 1, 2 and 4 */
	nvkm_wr32(device, 0x20000, 0x000003ff);

	/* shutdown: The computer should be shutdown when reached */
	nvkm_wr32(device, 0x20484, sensor->thrs_shutdown.hysteresis);
	nvkm_wr32(device, 0x20480, sensor->thrs_shutdown.temp);

	/* THRS_1 : fan boost*/
	nvkm_wr32(device, 0x204c4, sensor->thrs_fan_boost.temp);

	/* THRS_2 : critical */
	nvkm_wr32(device, 0x204c0, sensor->thrs_critical.temp);

	/* THRS_4 : down clock */
	nvkm_wr32(device, 0x20414, sensor->thrs_down_clock.temp);
	spin_unlock_irqrestore(&therm->sensor.alarm_program_lock, flags);

	nvkm_debug(subdev,
		   "Programmed thresholds [ %d(%d), %d(%d), %d(%d), %d(%d) ]\n",
		   sensor->thrs_fan_boost.temp,
		   sensor->thrs_fan_boost.hysteresis,
		   sensor->thrs_down_clock.temp,
		   sensor->thrs_down_clock.hysteresis,
		   sensor->thrs_critical.temp,
		   sensor->thrs_critical.hysteresis,
		   sensor->thrs_shutdown.temp,
		   sensor->thrs_shutdown.hysteresis);

}