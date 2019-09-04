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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  alarm_program_lock; } ;
struct nvbios_therm_sensor {int /*<<< orphan*/  thrs_critical; int /*<<< orphan*/  thrs_fan_boost; int /*<<< orphan*/  thrs_shutdown; int /*<<< orphan*/  thrs_down_clock; } ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_1__ sensor; struct nvbios_therm_sensor bios_sensor; struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_THERM_THRS_CRITICAL ; 
 int /*<<< orphan*/  NVKM_THERM_THRS_DOWNCLOCK ; 
 int /*<<< orphan*/  NVKM_THERM_THRS_FANBOOST ; 
 int /*<<< orphan*/  NVKM_THERM_THRS_SHUTDOWN ; 
 int /*<<< orphan*/  g84_therm_threshold_hyst_emulation (struct nvkm_therm*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
g84_therm_intr(struct nvkm_therm *therm)
{
	struct nvkm_subdev *subdev = &therm->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvbios_therm_sensor *sensor = &therm->bios_sensor;
	unsigned long flags;
	uint32_t intr;

	spin_lock_irqsave(&therm->sensor.alarm_program_lock, flags);

	intr = nvkm_rd32(device, 0x20100) & 0x3ff;

	/* THRS_4: downclock */
	if (intr & 0x002) {
		g84_therm_threshold_hyst_emulation(therm, 0x20414, 24,
						   &sensor->thrs_down_clock,
						   NVKM_THERM_THRS_DOWNCLOCK);
		intr &= ~0x002;
	}

	/* shutdown */
	if (intr & 0x004) {
		g84_therm_threshold_hyst_emulation(therm, 0x20480, 20,
						   &sensor->thrs_shutdown,
						   NVKM_THERM_THRS_SHUTDOWN);
		intr &= ~0x004;
	}

	/* THRS_1 : fan boost */
	if (intr & 0x008) {
		g84_therm_threshold_hyst_emulation(therm, 0x204c4, 21,
						   &sensor->thrs_fan_boost,
						   NVKM_THERM_THRS_FANBOOST);
		intr &= ~0x008;
	}

	/* THRS_2 : critical */
	if (intr & 0x010) {
		g84_therm_threshold_hyst_emulation(therm, 0x204c0, 22,
						   &sensor->thrs_critical,
						   NVKM_THERM_THRS_CRITICAL);
		intr &= ~0x010;
	}

	if (intr)
		nvkm_error(subdev, "intr %08x\n", intr);

	/* ACK everything */
	nvkm_wr32(device, 0x20100, 0xffffffff);
	nvkm_wr32(device, 0x1100, 0x10000); /* PBUS */

	spin_unlock_irqrestore(&therm->sensor.alarm_program_lock, flags);
}