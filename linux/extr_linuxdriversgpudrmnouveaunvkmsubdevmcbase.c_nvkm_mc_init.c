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
struct nvkm_subdev {int /*<<< orphan*/  device; } ;
struct nvkm_mc {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct nvkm_mc*) ;} ;

/* Variables and functions */
 struct nvkm_mc* nvkm_mc (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_mc_intr_rearm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_mc*) ; 

__attribute__((used)) static int
nvkm_mc_init(struct nvkm_subdev *subdev)
{
	struct nvkm_mc *mc = nvkm_mc(subdev);
	if (mc->func->init)
		mc->func->init(mc);
	nvkm_mc_intr_rearm(subdev->device);
	return 0;
}