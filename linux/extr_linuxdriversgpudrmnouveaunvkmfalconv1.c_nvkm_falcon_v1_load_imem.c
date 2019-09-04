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
typedef  int /*<<< orphan*/  u16 ;
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 

__attribute__((used)) static void
nvkm_falcon_v1_load_imem(struct nvkm_falcon *falcon, void *data, u32 start,
			 u32 size, u16 tag, u8 port, bool secure)
{
	u8 rem = size % 4;
	u32 reg;
	int i;

	size -= rem;

	reg = start | BIT(24) | (secure ? BIT(28) : 0);
	nvkm_falcon_wr32(falcon, 0x180 + (port * 16), reg);
	for (i = 0; i < size / 4; i++) {
		/* write new tag every 256B */
		if ((i & 0x3f) == 0)
			nvkm_falcon_wr32(falcon, 0x188 + (port * 16), tag++);
		nvkm_falcon_wr32(falcon, 0x184 + (port * 16), ((u32 *)data)[i]);
	}

	/*
	 * If size is not a multiple of 4, mask the last work to ensure garbage
	 * does not get written
	 */
	if (rem) {
		u32 extra = ((u32 *)data)[i];

		/* write new tag every 256B */
		if ((i & 0x3f) == 0)
			nvkm_falcon_wr32(falcon, 0x188 + (port * 16), tag++);
		nvkm_falcon_wr32(falcon, 0x184 + (port * 16),
				 extra & (BIT(rem * 8) - 1));
		++i;
	}

	/* code must be padded to 0x40 words */
	for (; i & 0x3f; i++)
		nvkm_falcon_wr32(falcon, 0x184 + (port * 16), 0);
}