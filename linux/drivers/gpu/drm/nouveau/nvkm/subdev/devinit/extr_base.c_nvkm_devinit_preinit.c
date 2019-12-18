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
struct nvkm_devinit {int force_post; int post; TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* preinit ) (struct nvkm_devinit*) ;} ;

/* Variables and functions */
 struct nvkm_devinit* nvkm_devinit (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_lockvgac (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_devinit*) ; 

__attribute__((used)) static int
nvkm_devinit_preinit(struct nvkm_subdev *subdev)
{
	struct nvkm_devinit *init = nvkm_devinit(subdev);

	if (init->func->preinit)
		init->func->preinit(init);

	/* Override the post flag during the first call if NvForcePost is set */
	if (init->force_post) {
		init->post = init->force_post;
		init->force_post = false;
	}

	/* unlock the extended vga crtc regs */
	nvkm_lockvgac(subdev->device, false);
	return 0;
}