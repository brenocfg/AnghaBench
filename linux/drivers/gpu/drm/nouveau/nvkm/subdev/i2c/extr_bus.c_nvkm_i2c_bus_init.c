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
struct nvkm_i2c_bus {int enabled; int /*<<< orphan*/  mutex; TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct nvkm_i2c_bus*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_TRACE (struct nvkm_i2c_bus*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_i2c_bus*) ; 

void
nvkm_i2c_bus_init(struct nvkm_i2c_bus *bus)
{
	BUS_TRACE(bus, "init");
	if (bus->func->init)
		bus->func->init(bus);

	mutex_lock(&bus->mutex);
	bus->enabled = true;
	mutex_unlock(&bus->mutex);
}