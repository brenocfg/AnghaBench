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
struct nvkm_therm {int /*<<< orphan*/  mode; int /*<<< orphan*/  suspend; TYPE_1__* func; } ;
struct nvkm_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fini ) (struct nvkm_therm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_THERM_CTRL_NONE ; 
 struct nvkm_therm* nvkm_therm (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_therm_fan_fini (struct nvkm_therm*,int) ; 
 int /*<<< orphan*/  nvkm_therm_sensor_fini (struct nvkm_therm*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_therm*) ; 

__attribute__((used)) static int
nvkm_therm_fini(struct nvkm_subdev *subdev, bool suspend)
{
	struct nvkm_therm *therm = nvkm_therm(subdev);

	if (therm->func->fini)
		therm->func->fini(therm);

	nvkm_therm_fan_fini(therm, suspend);
	nvkm_therm_sensor_fini(therm, suspend);

	if (suspend) {
		therm->suspend = therm->mode;
		therm->mode = NVKM_THERM_CTRL_NONE;
	}

	return 0;
}