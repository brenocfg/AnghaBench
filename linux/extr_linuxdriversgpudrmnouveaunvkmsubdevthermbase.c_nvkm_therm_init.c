#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_therm {scalar_t__ suspend; TYPE_2__* fan; TYPE_1__* func; } ;
struct nvkm_subdev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  percent; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init ) (struct nvkm_therm*) ;} ;

/* Variables and functions */
 struct nvkm_therm* nvkm_therm (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_therm_fan_init (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_therm_fan_mode (struct nvkm_therm*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_therm_fan_set (struct nvkm_therm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_therm_sensor_init (struct nvkm_therm*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_therm*) ; 

__attribute__((used)) static int
nvkm_therm_init(struct nvkm_subdev *subdev)
{
	struct nvkm_therm *therm = nvkm_therm(subdev);

	if (therm->func->init)
		therm->func->init(therm);

	if (therm->suspend >= 0) {
		/* restore the pwm value only when on manual or auto mode */
		if (therm->suspend > 0)
			nvkm_therm_fan_set(therm, true, therm->fan->percent);

		nvkm_therm_fan_mode(therm, therm->suspend);
	}

	nvkm_therm_sensor_init(therm);
	nvkm_therm_fan_init(therm);
	return 0;
}