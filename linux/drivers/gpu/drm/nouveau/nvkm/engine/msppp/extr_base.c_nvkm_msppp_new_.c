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
struct nvkm_falcon_func {int dummy; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_falcon_new_ (struct nvkm_falcon_func const*,struct nvkm_device*,int,int,int,struct nvkm_engine**) ; 

int
nvkm_msppp_new_(const struct nvkm_falcon_func *func, struct nvkm_device *device,
		int index, struct nvkm_engine **pengine)
{
	return nvkm_falcon_new_(func, device, index, true, 0x086000, pengine);
}