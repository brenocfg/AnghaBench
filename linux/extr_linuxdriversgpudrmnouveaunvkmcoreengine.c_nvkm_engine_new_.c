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
struct nvkm_engine_func {int dummy; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_engine* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_engine_ctor (struct nvkm_engine_func const*,struct nvkm_device*,int,int,struct nvkm_engine*) ; 

int
nvkm_engine_new_(const struct nvkm_engine_func *func,
		 struct nvkm_device *device, int index, bool enable,
		 struct nvkm_engine **pengine)
{
	if (!(*pengine = kzalloc(sizeof(**pengine), GFP_KERNEL)))
		return -ENOMEM;
	return nvkm_engine_ctor(func, device, index, enable, *pengine);
}