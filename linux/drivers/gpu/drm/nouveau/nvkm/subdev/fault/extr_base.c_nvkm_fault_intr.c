#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {int dummy; } ;
struct nvkm_fault {TYPE_1__* func; } ;
struct TYPE_2__ {void (* intr ) (struct nvkm_fault*) ;} ;

/* Variables and functions */
 struct nvkm_fault* nvkm_fault (struct nvkm_subdev*) ; 
 void stub1 (struct nvkm_fault*) ; 

__attribute__((used)) static void
nvkm_fault_intr(struct nvkm_subdev *subdev)
{
	struct nvkm_fault *fault = nvkm_fault(subdev);
	return fault->func->intr(fault);
}