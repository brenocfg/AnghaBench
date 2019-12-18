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
struct TYPE_2__ {struct nvkm_i2c_bus* algo_data; } ;
struct nvkm_i2c_bus {TYPE_1__ i2c; int /*<<< orphan*/  head; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_TRACE (struct nvkm_i2c_bus*,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct nvkm_i2c_bus*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
nvkm_i2c_bus_del(struct nvkm_i2c_bus **pbus)
{
	struct nvkm_i2c_bus *bus = *pbus;
	if (bus && !WARN_ON(!bus->func)) {
		BUS_TRACE(bus, "dtor");
		list_del(&bus->head);
		i2c_del_adapter(&bus->i2c);
		kfree(bus->i2c.algo_data);
		kfree(*pbus);
		*pbus = NULL;
	}
}