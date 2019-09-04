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
struct nvkm_therm {int dummy; } ;
struct nvkm_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_THERM_CTRL_AUTO ; 
 struct nvkm_therm* nvkm_therm (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_therm_clkgate_oneinit (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_therm_fan_ctor (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_therm_fan_mode (struct nvkm_therm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_therm_ic_ctor (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_therm_sensor_ctor (struct nvkm_therm*) ; 
 int /*<<< orphan*/  nvkm_therm_sensor_preinit (struct nvkm_therm*) ; 

__attribute__((used)) static int
nvkm_therm_oneinit(struct nvkm_subdev *subdev)
{
	struct nvkm_therm *therm = nvkm_therm(subdev);
	nvkm_therm_sensor_ctor(therm);
	nvkm_therm_ic_ctor(therm);
	nvkm_therm_fan_ctor(therm);
	nvkm_therm_fan_mode(therm, NVKM_THERM_CTRL_AUTO);
	nvkm_therm_sensor_preinit(therm);
	nvkm_therm_clkgate_oneinit(therm);
	return 0;
}