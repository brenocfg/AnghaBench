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
struct nvkm_mc {TYPE_1__* func; } ;
struct nvkm_device {struct nvkm_mc* mc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* intr_unarm ) (struct nvkm_mc*) ;} ;

/* Variables and functions */
 scalar_t__ likely (struct nvkm_mc*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_mc*) ; 

void
nvkm_mc_intr_unarm(struct nvkm_device *device)
{
	struct nvkm_mc *mc = device->mc;
	if (likely(mc))
		mc->func->intr_unarm(mc);
}