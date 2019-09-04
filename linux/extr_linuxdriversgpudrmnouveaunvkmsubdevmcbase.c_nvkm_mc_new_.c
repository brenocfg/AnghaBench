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
struct nvkm_mc {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_mc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_mc_ctor (struct nvkm_mc_func const*,struct nvkm_device*,int,struct nvkm_mc*) ; 

int
nvkm_mc_new_(const struct nvkm_mc_func *func, struct nvkm_device *device,
	     int index, struct nvkm_mc **pmc)
{
	struct nvkm_mc *mc;
	if (!(mc = *pmc = kzalloc(sizeof(*mc), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_mc_ctor(func, device, index, *pmc);
	return 0;
}