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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_vmm {TYPE_2__* func; } ;
struct nvkm_memory {int dummy; } ;
struct TYPE_4__ {TYPE_1__* page; } ;
struct TYPE_3__ {int shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 int gf100_vmm_join_ (struct nvkm_vmm*,struct nvkm_memory*,int /*<<< orphan*/ ) ; 

int
gm200_vmm_join_(struct nvkm_vmm *vmm, struct nvkm_memory *inst, u64 base)
{
	if (vmm->func->page[1].shift == 16)
		base |= BIT_ULL(11);
	return gf100_vmm_join_(vmm, inst, base);
}