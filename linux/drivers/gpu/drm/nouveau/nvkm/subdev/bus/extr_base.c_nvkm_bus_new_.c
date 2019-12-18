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
struct nvkm_device {int dummy; } ;
struct nvkm_bus_func {int dummy; } ;
struct nvkm_bus {struct nvkm_bus_func const* func; int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_bus ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 

int
nvkm_bus_new_(const struct nvkm_bus_func *func, struct nvkm_device *device,
	      int index, struct nvkm_bus **pbus)
{
	struct nvkm_bus *bus;
	if (!(bus = *pbus = kzalloc(sizeof(*bus), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_subdev_ctor(&nvkm_bus, device, index, &bus->subdev);
	bus->func = func;
	return 0;
}