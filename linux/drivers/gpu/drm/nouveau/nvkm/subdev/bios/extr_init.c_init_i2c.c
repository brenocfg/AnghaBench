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
struct i2c_adapter {int dummy; } ;
struct nvkm_i2c_bus {struct i2c_adapter i2c; } ;
struct nvkm_i2c {int dummy; } ;
struct nvbios_init {TYPE_3__* outp; TYPE_2__* subdev; } ;
struct TYPE_6__ {scalar_t__ i2c_upper_default; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {struct nvkm_i2c* i2c; } ;

/* Variables and functions */
 int NVKM_I2C_BUS_PRI ; 
 int NVKM_I2C_BUS_SEC ; 
 struct nvkm_i2c_bus* nvkm_i2c_bus_find (struct nvkm_i2c*,int) ; 

__attribute__((used)) static struct i2c_adapter *
init_i2c(struct nvbios_init *init, int index)
{
	struct nvkm_i2c *i2c = init->subdev->device->i2c;
	struct nvkm_i2c_bus *bus;

	if (index == 0xff) {
		index = NVKM_I2C_BUS_PRI;
		if (init->outp && init->outp->i2c_upper_default)
			index = NVKM_I2C_BUS_SEC;
	} else
	if (index == 0x80) {
		index = NVKM_I2C_BUS_PRI;
	} else
	if (index == 0x81) {
		index = NVKM_I2C_BUS_SEC;
	}

	bus = nvkm_i2c_bus_find(i2c, index);
	return bus ? &bus->i2c : NULL;
}