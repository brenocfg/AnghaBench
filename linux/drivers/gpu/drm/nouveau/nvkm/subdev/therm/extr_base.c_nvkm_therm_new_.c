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
struct nvkm_therm_func {int dummy; } ;
struct nvkm_therm {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_therm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_therm_ctor (struct nvkm_therm*,struct nvkm_device*,int,struct nvkm_therm_func const*) ; 

int
nvkm_therm_new_(const struct nvkm_therm_func *func, struct nvkm_device *device,
		int index, struct nvkm_therm **ptherm)
{
	struct nvkm_therm *therm;

	if (!(therm = *ptherm = kzalloc(sizeof(*therm), GFP_KERNEL)))
		return -ENOMEM;

	nvkm_therm_ctor(therm, device, index, func);
	return 0;
}