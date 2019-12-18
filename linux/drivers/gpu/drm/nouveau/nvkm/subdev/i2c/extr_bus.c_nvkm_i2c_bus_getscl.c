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
struct nvkm_i2c_bus {TYPE_1__* func; } ;
struct TYPE_2__ {int (* sense_scl ) (struct nvkm_i2c_bus*) ;} ;

/* Variables and functions */
 int stub1 (struct nvkm_i2c_bus*) ; 

__attribute__((used)) static int
nvkm_i2c_bus_getscl(void *data)
{
	struct nvkm_i2c_bus *bus = data;
	return bus->func->sense_scl(bus);
}