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
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 

__attribute__((used)) static void
nvkm_falcon_v1_load_emem(struct nvkm_falcon *falcon, void *data, u32 start,
			 u32 size, u8 port)
{
	u8 rem = size % 4;
	int i;

	size -= rem;

	nvkm_falcon_wr32(falcon, 0xac0 + (port * 8), start | (0x1 << 24));
	for (i = 0; i < size / 4; i++)
		nvkm_falcon_wr32(falcon, 0xac4 + (port * 8), ((u32 *)data)[i]);

	/*
	 * If size is not a multiple of 4, mask the last word to ensure garbage
	 * does not get written
	 */
	if (rem) {
		u32 extra = ((u32 *)data)[i];

		nvkm_falcon_wr32(falcon, 0xac4 + (port * 8),
				 extra & (BIT(rem * 8) - 1));
	}
}