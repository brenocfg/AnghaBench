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
struct nvkm_vmm {int dummy; } ;
struct nvkm_device {TYPE_3__* bar; } ;
struct TYPE_6__ {TYPE_2__* func; } ;
struct TYPE_4__ {struct nvkm_vmm* (* vmm ) (TYPE_3__*) ;} ;
struct TYPE_5__ {TYPE_1__ bar1; } ;

/* Variables and functions */
 struct nvkm_vmm* stub1 (TYPE_3__*) ; 

struct nvkm_vmm *
nvkm_bar_bar1_vmm(struct nvkm_device *device)
{
	return device->bar->func->bar1.vmm(device->bar);
}