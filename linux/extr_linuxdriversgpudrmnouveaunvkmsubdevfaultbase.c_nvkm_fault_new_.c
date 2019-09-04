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
struct nvkm_fault_func {int dummy; } ;
struct nvkm_fault {struct nvkm_fault_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_fault* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_fault ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 

int
nvkm_fault_new_(const struct nvkm_fault_func *func, struct nvkm_device *device,
		int index, struct nvkm_fault **pfault)
{
	struct nvkm_fault *fault;
	if (!(fault = *pfault = kzalloc(sizeof(*fault), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_subdev_ctor(&nvkm_fault, device, index, &fault->subdev);
	fault->func = func;
	return 0;
}