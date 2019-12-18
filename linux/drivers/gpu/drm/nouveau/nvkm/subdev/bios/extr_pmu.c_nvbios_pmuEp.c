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
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_pmuE {int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_pmuE*,int,int) ; 
 scalar_t__ nvbios_pmuEe (struct nvkm_bios*,int,int*,int*) ; 
 int /*<<< orphan*/  nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_pmuEp(struct nvkm_bios *bios, int idx, u8 *ver, u8 *hdr,
	     struct nvbios_pmuE *info)
{
	u32 data = nvbios_pmuEe(bios, idx, ver, hdr);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *ver) {
	default:
		info->type = nvbios_rd08(bios, data + 0x00);
		info->data = nvbios_rd32(bios, data + 0x02);
		break;
	}
	return data;
}