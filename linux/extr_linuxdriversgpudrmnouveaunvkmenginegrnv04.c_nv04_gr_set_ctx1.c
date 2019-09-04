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
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int NV04_PGRAPH_CTX_CACHE1 ; 
 int NV04_PGRAPH_CTX_SWITCH1 ; 
 int NV04_PGRAPH_TRAPPED_ADDR ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv04_gr_set_ctx1(struct nvkm_device *device, u32 inst, u32 mask, u32 value)
{
	int subc = (nvkm_rd32(device, NV04_PGRAPH_TRAPPED_ADDR) >> 13) & 0x7;
	u32 tmp;

	tmp  = nvkm_rd32(device, 0x700000 + inst);
	tmp &= ~mask;
	tmp |= value;
	nvkm_wr32(device, 0x700000 + inst, tmp);

	nvkm_wr32(device, NV04_PGRAPH_CTX_SWITCH1, tmp);
	nvkm_wr32(device, NV04_PGRAPH_CTX_CACHE1 + (subc << 2), tmp);
}