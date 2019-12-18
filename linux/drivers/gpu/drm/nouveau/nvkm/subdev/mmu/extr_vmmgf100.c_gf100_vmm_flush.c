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
typedef  int u32 ;
struct nvkm_vmm {int /*<<< orphan*/ * engref; } ;

/* Variables and functions */
 size_t NVKM_SUBDEV_BAR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gf100_vmm_invalidate (struct nvkm_vmm*,int) ; 

void
gf100_vmm_flush(struct nvkm_vmm *vmm, int depth)
{
	u32 type = 0x00000001; /* PAGE_ALL */
	if (atomic_read(&vmm->engref[NVKM_SUBDEV_BAR]))
		type |= 0x00000004; /* HUB_ONLY */
	gf100_vmm_invalidate(vmm, type);
}