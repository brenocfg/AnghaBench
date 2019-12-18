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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_xtensa_func {int dummy; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_xtensa {struct nvkm_engine engine; int /*<<< orphan*/  addr; struct nvkm_xtensa_func const* func; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_xtensa* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,struct nvkm_engine*) ; 
 int /*<<< orphan*/  nvkm_xtensa ; 

int
nvkm_xtensa_new_(const struct nvkm_xtensa_func *func,
		 struct nvkm_device *device, int index, bool enable,
		 u32 addr, struct nvkm_engine **pengine)
{
	struct nvkm_xtensa *xtensa;

	if (!(xtensa = kzalloc(sizeof(*xtensa), GFP_KERNEL)))
		return -ENOMEM;
	xtensa->func = func;
	xtensa->addr = addr;
	*pengine = &xtensa->engine;

	return nvkm_engine_ctor(&nvkm_xtensa, device, index,
				enable, &xtensa->engine);
}