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
struct nvkm_oclass {int /*<<< orphan*/  base; } ;
struct nvkm_device_oclass {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct nvkm_device_oclass nvkm_pm_oclass ; 

__attribute__((used)) static int
nvkm_pm_oclass_get(struct nvkm_oclass *oclass, int index,
		   const struct nvkm_device_oclass **class)
{
	if (index == 0) {
		oclass->base = nvkm_pm_oclass.base;
		*class = &nvkm_pm_oclass;
		return index;
	}
	return 1;
}