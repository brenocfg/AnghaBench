#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvkm_mmu {int dummy; } ;
struct nvkm_device {scalar_t__ type; int /*<<< orphan*/  cfgopt; } ;

/* Variables and functions */
 scalar_t__ NVKM_DEVICE_AGP ; 
 int nv04_mmu_new (struct nvkm_device*,int,struct nvkm_mmu**) ; 
 int /*<<< orphan*/  nv44_mmu ; 
 int /*<<< orphan*/  nvkm_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int nvkm_mmu_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_mmu**) ; 

int
nv44_mmu_new(struct nvkm_device *device, int index, struct nvkm_mmu **pmmu)
{
	if (device->type == NVKM_DEVICE_AGP ||
	    !nvkm_boolopt(device->cfgopt, "NvPCIE", true))
		return nv04_mmu_new(device, index, pmmu);

	return nvkm_mmu_new_(&nv44_mmu, device, index, pmmu);
}