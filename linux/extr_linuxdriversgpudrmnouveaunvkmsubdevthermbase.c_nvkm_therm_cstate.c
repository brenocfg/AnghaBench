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
struct nvkm_subdev {int dummy; } ;
struct nvkm_therm {int cstate; struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int) ; 
 int /*<<< orphan*/  nvkm_therm_update (struct nvkm_therm*,int) ; 

int
nvkm_therm_cstate(struct nvkm_therm *therm, int fan, int dir)
{
	struct nvkm_subdev *subdev = &therm->subdev;
	if (!dir || (dir < 0 && fan < therm->cstate) ||
		    (dir > 0 && fan > therm->cstate)) {
		nvkm_debug(subdev, "default fan speed -> %d%%\n", fan);
		therm->cstate = fan;
		nvkm_therm_update(therm, -1);
	}
	return 0;
}