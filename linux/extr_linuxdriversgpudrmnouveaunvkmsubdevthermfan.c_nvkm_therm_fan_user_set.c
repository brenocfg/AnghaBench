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
struct nvkm_therm {scalar_t__ mode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NVKM_THERM_CTRL_MANUAL ; 
 int nvkm_therm_fan_set (struct nvkm_therm*,int,int) ; 

int
nvkm_therm_fan_user_set(struct nvkm_therm *therm, int percent)
{
	if (therm->mode != NVKM_THERM_CTRL_MANUAL)
		return -EINVAL;

	return nvkm_therm_fan_set(therm, true, percent);
}