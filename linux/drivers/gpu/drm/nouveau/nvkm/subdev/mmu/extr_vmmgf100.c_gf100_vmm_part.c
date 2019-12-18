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
struct nvkm_vmm {int dummy; } ;
struct nvkm_memory {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_fo64 (struct nvkm_memory*,int,int,int) ; 

void
gf100_vmm_part(struct nvkm_vmm *vmm, struct nvkm_memory *inst)
{
	nvkm_fo64(inst, 0x0200, 0x00000000, 2);
}