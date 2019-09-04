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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_cstepX {int freq; void* voltage; void** unkn; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_cstepX*,int,int) ; 
 scalar_t__ nvbios_cstepXe (struct nvkm_bios*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_cstepXp(struct nvkm_bios *bios, int idx, u8 *ver, u8 *hdr,
	       struct nvbios_cstepX *info)
{
	u32 data = nvbios_cstepXe(bios, idx, ver, hdr);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->freq    = nvbios_rd16(bios, data + 0x00) * 1000;
		info->unkn[0] = nvbios_rd08(bios, data + 0x02);
		info->unkn[1] = nvbios_rd08(bios, data + 0x03);
		info->voltage = nvbios_rd08(bios, data + 0x04);
	}
	return data;
}