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
struct nvkm_device {int dummy; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_bus {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gf100_bus_init(struct nvkm_bus *bus)
{
	struct nvkm_device *device = bus->subdev.device;
	nvkm_wr32(device, 0x001100, 0xffffffff);
	nvkm_wr32(device, 0x001140, 0x0000000e);
}