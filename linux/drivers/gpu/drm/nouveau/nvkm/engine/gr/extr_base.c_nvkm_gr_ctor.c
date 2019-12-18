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
struct nvkm_gr_func {int dummy; } ;
struct nvkm_gr {int /*<<< orphan*/  engine; struct nvkm_gr_func const* func; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_gr ; 

int
nvkm_gr_ctor(const struct nvkm_gr_func *func, struct nvkm_device *device,
	     int index, bool enable, struct nvkm_gr *gr)
{
	gr->func = func;
	return nvkm_engine_ctor(&nvkm_gr, device, index, enable, &gr->engine);
}