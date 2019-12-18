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
typedef  int u8 ;
typedef  int u32 ;
struct nvkm_falcon {scalar_t__ has_emem; } ;

/* Variables and functions */
 int EMEM_START_ADDR ; 
 int nvkm_falcon_rd32 (struct nvkm_falcon*,int) ; 
 void nvkm_falcon_v1_read_emem (struct nvkm_falcon*,int,int,int,void*) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 

__attribute__((used)) static void
nvkm_falcon_v1_read_dmem(struct nvkm_falcon *falcon, u32 start, u32 size,
			 u8 port, void *data)
{
	u8 rem = size % 4;
	int i;

	if (start >= EMEM_START_ADDR && falcon->has_emem)
		return nvkm_falcon_v1_read_emem(falcon, start - EMEM_START_ADDR,
						size, port, data);

	size -= rem;

	nvkm_falcon_wr32(falcon, 0x1c0 + (port * 8), start | (0x1 << 25));
	for (i = 0; i < size / 4; i++)
		((u32 *)data)[i] = nvkm_falcon_rd32(falcon, 0x1c4 + (port * 8));

	/*
	 * If size is not a multiple of 4, mask the last word to ensure garbage
	 * does not get read
	 */
	if (rem) {
		u32 extra = nvkm_falcon_rd32(falcon, 0x1c4 + (port * 8));

		for (i = size; i < size + rem; i++) {
			((u8 *)data)[i] = (u8)(extra & 0xff);
			extra >>= 8;
		}
	}
}