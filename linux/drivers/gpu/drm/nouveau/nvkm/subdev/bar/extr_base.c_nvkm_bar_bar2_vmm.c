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
struct nvkm_vmm {int dummy; } ;
struct nvkm_device {struct nvkm_bar* bar; } ;
struct nvkm_bar {TYPE_2__* func; scalar_t__ bar2; } ;
struct TYPE_3__ {struct nvkm_vmm* (* vmm ) (struct nvkm_bar*) ;} ;
struct TYPE_4__ {TYPE_1__ bar2; } ;

/* Variables and functions */
 struct nvkm_vmm* stub1 (struct nvkm_bar*) ; 

struct nvkm_vmm *
nvkm_bar_bar2_vmm(struct nvkm_device *device)
{
	/* Denies access to BAR2 when it's not initialised, used by INSTMEM
	 * to know when object access needs to go through the BAR0 window.
	 */
	struct nvkm_bar *bar = device->bar;
	if (bar && bar->bar2)
		return bar->func->bar2.vmm(bar);
	return NULL;
}