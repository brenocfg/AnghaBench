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
struct nvkm_fb {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* intr ) (struct nvkm_fb*) ;} ;

/* Variables and functions */
 struct nvkm_fb* nvkm_fb (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_fb*) ; 

__attribute__((used)) static void
nvkm_fb_intr(struct nvkm_subdev *subdev)
{
	struct nvkm_fb *fb = nvkm_fb(subdev);
	if (fb->func->intr)
		fb->func->intr(fb);
}