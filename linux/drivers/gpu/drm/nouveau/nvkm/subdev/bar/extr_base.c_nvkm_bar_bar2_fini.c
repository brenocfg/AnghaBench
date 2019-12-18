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
struct nvkm_device {struct nvkm_bar* bar; } ;
struct nvkm_bar {int bar2; TYPE_2__* func; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fini ) (struct nvkm_bar*) ;} ;
struct TYPE_4__ {TYPE_1__ bar2; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_bar*) ; 

void
nvkm_bar_bar2_fini(struct nvkm_device *device)
{
	struct nvkm_bar *bar = device->bar;
	if (bar && bar->bar2) {
		bar->func->bar2.fini(bar);
		bar->bar2 = false;
	}
}