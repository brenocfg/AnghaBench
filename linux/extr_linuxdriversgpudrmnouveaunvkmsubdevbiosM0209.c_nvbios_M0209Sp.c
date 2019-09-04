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
typedef  int u16 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_M0209S {int* data; } ;
struct nvbios_M0209E {int modulo; int bits; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  memset (struct nvbios_M0209S*,int,int) ; 
 int nvbios_M0209Ep (struct nvkm_bios*,int,int*,int*,int*,int*,struct nvbios_M0209E*) ; 
 int nvbios_M0209Se (struct nvkm_bios*,int,int,int*,int*) ; 
 int nvbios_rd32 (struct nvkm_bios*,int) ; 

u32
nvbios_M0209Sp(struct nvkm_bios *bios, int ent, int idx, u8 *ver, u8 *hdr,
	       struct nvbios_M0209S *info)
{
	struct nvbios_M0209E M0209E;
	u8  cnt, len;
	u32 data = nvbios_M0209Ep(bios, ent, ver, hdr, &cnt, &len, &M0209E);
	if (data) {
		u32 i, data = nvbios_M0209Se(bios, ent, idx, ver, hdr);
		memset(info, 0x00, sizeof(*info));
		switch (!!data * *ver) {
		case 0x10:
			for (i = 0; i < ARRAY_SIZE(info->data); i++) {
				u32 bits = (i % M0209E.modulo) * M0209E.bits;
				u32 mask = (1ULL << M0209E.bits) - 1;
				u16  off = bits / 8;
				u8   mod = bits % 8;
				info->data[i] = nvbios_rd32(bios, data + off);
				info->data[i] = info->data[i] >> mod;
				info->data[i] = info->data[i] & mask;
			}
			return data;
		default:
			break;
		}
	}
	return 0x00000000;
}