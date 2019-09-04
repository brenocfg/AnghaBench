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
typedef  int u64 ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_memory {int dummy; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int gf100_vmm_join_ (struct nvkm_vmm*,struct nvkm_memory*,int const) ; 

int
gp100_vmm_join(struct nvkm_vmm *vmm, struct nvkm_memory *inst)
{
	const u64 base = BIT_ULL(10) /* VER2 */ | BIT_ULL(11); /* 64KiB */
	return gf100_vmm_join_(vmm, inst, base);
}