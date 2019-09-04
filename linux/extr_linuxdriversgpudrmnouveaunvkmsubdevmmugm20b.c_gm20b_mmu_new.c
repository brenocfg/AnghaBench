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
struct nvkm_mmu {int dummy; } ;
struct nvkm_device {TYPE_1__* fb; } ;
struct TYPE_2__ {scalar_t__ page; } ;

/* Variables and functions */
 int /*<<< orphan*/  gm20b_mmu ; 
 int /*<<< orphan*/  gm20b_mmu_fixed ; 
 int nvkm_mmu_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_mmu**) ; 

int
gm20b_mmu_new(struct nvkm_device *device, int index, struct nvkm_mmu **pmmu)
{
	if (device->fb->page)
		return nvkm_mmu_new_(&gm20b_mmu_fixed, device, index, pmmu);
	return nvkm_mmu_new_(&gm20b_mmu, device, index, pmmu);
}