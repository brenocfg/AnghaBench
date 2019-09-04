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
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
g84_therm_fini(struct nvkm_therm *therm)
{
	struct nvkm_device *device = therm->subdev.device;

	/* Disable PTherm IRQs */
	nvkm_wr32(device, 0x20000, 0x00000000);

	/* ACK all PTherm IRQs */
	nvkm_wr32(device, 0x20100, 0xffffffff);
	nvkm_wr32(device, 0x1100, 0x10000); /* PBUS */
}