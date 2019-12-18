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
struct nvkm_i2c_pad {int dummy; } ;
struct nvkm_i2c_bus {int /*<<< orphan*/  mutex; scalar_t__ enabled; struct nvkm_i2c_pad* pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_TRACE (struct nvkm_i2c_bus*,char*) ; 
 int EIO ; 
 int /*<<< orphan*/  NVKM_I2C_PAD_I2C ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvkm_i2c_pad_acquire (struct nvkm_i2c_pad*,int /*<<< orphan*/ ) ; 

int
nvkm_i2c_bus_acquire(struct nvkm_i2c_bus *bus)
{
	struct nvkm_i2c_pad *pad = bus->pad;
	int ret;

	BUS_TRACE(bus, "acquire");
	mutex_lock(&bus->mutex);

	if (bus->enabled)
		ret = nvkm_i2c_pad_acquire(pad, NVKM_I2C_PAD_I2C);
	else
		ret = -EIO;

	if (ret)
		mutex_unlock(&bus->mutex);
	return ret;
}