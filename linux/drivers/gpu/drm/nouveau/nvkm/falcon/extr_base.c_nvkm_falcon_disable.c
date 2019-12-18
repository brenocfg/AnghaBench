#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_falcon {TYPE_2__* func; TYPE_1__* owner; } ;
struct nvkm_device {int dummy; } ;
typedef  enum nvkm_devidx { ____Placeholder_nvkm_devidx } nvkm_devidx ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (struct nvkm_falcon*) ;} ;
struct TYPE_3__ {int index; struct nvkm_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mc_disable (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_mc_enabled (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_falcon*) ; 

void
nvkm_falcon_disable(struct nvkm_falcon *falcon)
{
	struct nvkm_device *device = falcon->owner->device;
	enum nvkm_devidx id = falcon->owner->index;

	/* already disabled, return or wait_idle will timeout */
	if (!nvkm_mc_enabled(device, id))
		return;

	falcon->func->disable(falcon);

	nvkm_mc_disable(device, id);
}