#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_2__* fan; TYPE_1__ subdev; } ;
struct nvkm_device {int crystal; } ;
struct TYPE_6__ {scalar_t__ func; int line; } ;
struct TYPE_5__ {TYPE_3__ tach; } ;

/* Variables and functions */
 scalar_t__ DCB_GPIO_UNUSED ; 
 int /*<<< orphan*/  g84_sensor_setup (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
gf119_therm_init(struct nvkm_therm *therm)
{
	struct nvkm_device *device = therm->subdev.device;

	g84_sensor_setup(therm);

	/* enable fan tach, count revolutions per-second */
	nvkm_mask(device, 0x00e720, 0x00000003, 0x00000002);
	if (therm->fan->tach.func != DCB_GPIO_UNUSED) {
		nvkm_mask(device, 0x00d79c, 0x000000ff, therm->fan->tach.line);
		nvkm_wr32(device, 0x00e724, device->crystal * 1000);
		nvkm_mask(device, 0x00e720, 0x00000001, 0x00000001);
	}
	nvkm_mask(device, 0x00e720, 0x00000002, 0x00000000);
}