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
typedef  int u8 ;
struct nvkm_i2c_pad {int dummy; } ;
struct nvkm_i2c_bus {int dummy; } ;
struct gf119_i2c_bus {int addr; struct nvkm_i2c_bus base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gf119_i2c_bus_func ; 
 struct gf119_i2c_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_i2c_bus_ctor (int /*<<< orphan*/ *,struct nvkm_i2c_pad*,int,struct nvkm_i2c_bus*) ; 

int
gf119_i2c_bus_new(struct nvkm_i2c_pad *pad, int id, u8 drive,
		 struct nvkm_i2c_bus **pbus)
{
	struct gf119_i2c_bus *bus;

	if (!(bus = kzalloc(sizeof(*bus), GFP_KERNEL)))
		return -ENOMEM;
	*pbus = &bus->base;

	nvkm_i2c_bus_ctor(&gf119_i2c_bus_func, pad, id, &bus->base);
	bus->addr = 0x00d014 + (drive * 0x20);
	return 0;
}