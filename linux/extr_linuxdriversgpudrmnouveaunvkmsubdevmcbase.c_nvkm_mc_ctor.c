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
struct nvkm_mc_func {int dummy; } ;
struct nvkm_mc {struct nvkm_mc_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mc ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 

void
nvkm_mc_ctor(const struct nvkm_mc_func *func, struct nvkm_device *device,
	     int index, struct nvkm_mc *mc)
{
	nvkm_subdev_ctor(&nvkm_mc, device, index, &mc->subdev);
	mc->func = func;
}