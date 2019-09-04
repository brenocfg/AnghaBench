#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_device {struct nvkm_bar* bar; } ;
struct TYPE_4__ {scalar_t__ oneinit; } ;
struct nvkm_bar {int bar2; TYPE_2__* func; TYPE_1__ subdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* wait ) (struct nvkm_bar*) ;int /*<<< orphan*/  (* init ) (struct nvkm_bar*) ;} ;
struct TYPE_5__ {TYPE_3__ bar2; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_bar*) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_bar*) ; 

void
nvkm_bar_bar2_init(struct nvkm_device *device)
{
	struct nvkm_bar *bar = device->bar;
	if (bar && bar->subdev.oneinit && !bar->bar2 && bar->func->bar2.init) {
		bar->func->bar2.init(bar);
		bar->func->bar2.wait(bar);
		bar->bar2 = true;
	}
}