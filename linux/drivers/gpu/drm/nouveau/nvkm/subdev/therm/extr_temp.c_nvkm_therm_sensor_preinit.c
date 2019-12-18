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
struct nvkm_therm {int /*<<< orphan*/  subdev; TYPE_1__* func; } ;
struct TYPE_2__ {scalar_t__ (* temp_get ) (struct nvkm_therm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ stub1 (struct nvkm_therm*) ; 

void
nvkm_therm_sensor_preinit(struct nvkm_therm *therm)
{
	const char *sensor_avail = "yes";

	if (therm->func->temp_get(therm) < 0)
		sensor_avail = "no";

	nvkm_debug(&therm->subdev, "internal sensor: %s\n", sensor_avail);
}