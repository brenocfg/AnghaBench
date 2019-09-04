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
struct nvkm_bar {TYPE_1__* func; } ;
struct TYPE_2__ {void* (* dtor ) (struct nvkm_bar*) ;} ;

/* Variables and functions */
 struct nvkm_bar* nvkm_bar (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_bar_bar2_fini (int /*<<< orphan*/ ) ; 
 void* stub1 (struct nvkm_bar*) ; 

__attribute__((used)) static void *
nvkm_bar_dtor(struct nvkm_subdev *subdev)
{
	struct nvkm_bar *bar = nvkm_bar(subdev);
	nvkm_bar_bar2_fini(subdev->device);
	return bar->func->dtor(bar);
}