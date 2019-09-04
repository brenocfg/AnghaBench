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
struct nvkm_subdev {int dummy; } ;
struct nvkm_bar {TYPE_2__* func; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fini ) (struct nvkm_bar*) ;} ;
struct TYPE_4__ {TYPE_1__ bar1; } ;

/* Variables and functions */
 struct nvkm_bar* nvkm_bar (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_bar*) ; 

__attribute__((used)) static int
nvkm_bar_fini(struct nvkm_subdev *subdev, bool suspend)
{
	struct nvkm_bar *bar = nvkm_bar(subdev);
	if (bar->func->bar1.fini)
		bar->func->bar1.fini(bar);
	return 0;
}