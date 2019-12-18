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
 int /*<<< orphan*/  gk104_clkgate_engine_info ; 
 int /*<<< orphan*/  gk104_idle_filter ; 
 int /*<<< orphan*/  gk104_therm_func ; 
 int gk104_therm_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nvkm_therm**) ; 

int
gk104_therm_new(struct nvkm_device *device,
		int index, struct nvkm_therm **ptherm)
{
	return gk104_therm_new_(&gk104_therm_func, device, index,
				gk104_clkgate_engine_info, &gk104_idle_filter,
				ptherm);
}