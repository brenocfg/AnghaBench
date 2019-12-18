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
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_THERM_THRS_CRITICAL ; 
 int /*<<< orphan*/  NVKM_THERM_THRS_DOWNCLOCK ; 
 int /*<<< orphan*/  NVKM_THERM_THRS_FANBOOST ; 
 int /*<<< orphan*/  NVKM_THERM_THRS_LOWER ; 
 int /*<<< orphan*/  NVKM_THERM_THRS_SHUTDOWN ; 
 int /*<<< orphan*/  g84_therm ; 
 int nvkm_therm_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_therm**) ; 
 int /*<<< orphan*/  nvkm_therm_sensor_set_threshold_state (struct nvkm_therm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
g84_therm_new(struct nvkm_device *device, int index, struct nvkm_therm **ptherm)
{
	struct nvkm_therm *therm;
	int ret;

	ret = nvkm_therm_new_(&g84_therm, device, index, &therm);
	*ptherm = therm;
	if (ret)
		return ret;

	/* init the thresholds */
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_SHUTDOWN,
						     NVKM_THERM_THRS_LOWER);
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_FANBOOST,
						     NVKM_THERM_THRS_LOWER);
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_CRITICAL,
						     NVKM_THERM_THRS_LOWER);
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_DOWNCLOCK,
						     NVKM_THERM_THRS_LOWER);
	return 0;
}