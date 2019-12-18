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
struct nvkm_volt_func {int dummy; } ;
struct nvkm_volt {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_volt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_volt_ctor (struct nvkm_volt_func const*,struct nvkm_device*,int,struct nvkm_volt*) ; 

int
nvkm_volt_new_(const struct nvkm_volt_func *func, struct nvkm_device *device,
	       int index, struct nvkm_volt **pvolt)
{
	if (!(*pvolt = kzalloc(sizeof(**pvolt), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_volt_ctor(func, device, index, *pvolt);
	return 0;
}