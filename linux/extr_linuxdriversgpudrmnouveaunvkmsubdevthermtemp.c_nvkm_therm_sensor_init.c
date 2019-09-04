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
struct nvkm_therm {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* program_alarms ) (struct nvkm_therm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_therm*) ; 

int
nvkm_therm_sensor_init(struct nvkm_therm *therm)
{
	therm->func->program_alarms(therm);
	return 0;
}