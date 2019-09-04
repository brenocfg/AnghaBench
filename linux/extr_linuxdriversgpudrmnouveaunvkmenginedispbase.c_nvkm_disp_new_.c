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
struct nvkm_disp_func {int dummy; } ;
struct nvkm_disp {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_disp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_disp_ctor (struct nvkm_disp_func const*,struct nvkm_device*,int,struct nvkm_disp*) ; 

int
nvkm_disp_new_(const struct nvkm_disp_func *func, struct nvkm_device *device,
	       int index, struct nvkm_disp **pdisp)
{
	if (!(*pdisp = kzalloc(sizeof(**pdisp), GFP_KERNEL)))
		return -ENOMEM;
	return nvkm_disp_ctor(func, device, index, *pdisp);
}