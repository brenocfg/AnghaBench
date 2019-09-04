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
struct nvkm_i2c_bus {int /*<<< orphan*/  mutex; struct nvkm_i2c_pad* pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_TRACE (struct nvkm_i2c_bus*,char*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_i2c_pad_release (struct nvkm_i2c_pad*) ; 

void
nvkm_i2c_bus_release(struct nvkm_i2c_bus *bus)
{
	struct nvkm_i2c_pad *pad = bus->pad;
	BUS_TRACE(bus, "release");
	nvkm_i2c_pad_release(pad);
	mutex_unlock(&bus->mutex);
}