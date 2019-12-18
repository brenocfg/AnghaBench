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
struct nvbios_ramcfg {int ramcfg_ver; int ramcfg_hdr; int ramcfg_timing; int ramcfg_10_02_01; int ramcfg_10_02_02; int ramcfg_10_02_04; int ramcfg_10_02_08; int ramcfg_10_02_10; int ramcfg_10_02_20; int ramcfg_DLLoff; int ramcfg_10_03_0f; int ramcfg_10_04_01; int ramcfg_FBVDDQ; int ramcfg_10_05; int ramcfg_10_06; int ramcfg_10_07; int ramcfg_10_08; int ramcfg_10_09_0f; int ramcfg_10_09_f0; int ramcfg_11_01_01; int ramcfg_11_01_02; int ramcfg_11_01_04; int ramcfg_11_01_08; int ramcfg_11_01_10; int ramcfg_11_01_40; int ramcfg_11_01_80; int ramcfg_11_02_03; int ramcfg_11_02_04; int ramcfg_11_02_08; int ramcfg_11_02_10; int ramcfg_11_02_40; int ramcfg_11_02_80; int ramcfg_11_03_0f; int ramcfg_11_03_30; int ramcfg_11_03_c0; int ramcfg_11_03_f0; int ramcfg_11_04; int ramcfg_11_06; int ramcfg_11_07_02; int ramcfg_11_07_04; int ramcfg_11_07_08; int ramcfg_11_07_10; int ramcfg_11_07_40; int ramcfg_11_07_80; int ramcfg_11_08_01; int ramcfg_11_08_02; int ramcfg_11_08_04; int ramcfg_11_08_08; int ramcfg_11_08_10; int ramcfg_11_08_20; int ramcfg_11_09; } ;

/* Variables and functions */
 scalar_t__ nvbios_rammapSe (struct nvkm_bios*,scalar_t__,int,int,int,int,int,int*,int*) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_rammapSp(struct nvkm_bios *bios, u32 data,
		u8 ever, u8 ehdr, u8 ecnt, u8 elen, int idx,
		u8 *ver, u8 *hdr, struct nvbios_ramcfg *p)
{
	data = nvbios_rammapSe(bios, data, ever, ehdr, ecnt, elen, idx, ver, hdr);
	p->ramcfg_ver = *ver;
	p->ramcfg_hdr = *hdr;
	switch (!!data * *ver) {
	case 0x10:
		p->ramcfg_timing   =  nvbios_rd08(bios, data + 0x01);
		p->ramcfg_10_02_01 = (nvbios_rd08(bios, data + 0x02) & 0x01) >> 0;
		p->ramcfg_10_02_02 = (nvbios_rd08(bios, data + 0x02) & 0x02) >> 1;
		p->ramcfg_10_02_04 = (nvbios_rd08(bios, data + 0x02) & 0x04) >> 2;
		p->ramcfg_10_02_08 = (nvbios_rd08(bios, data + 0x02) & 0x08) >> 3;
		p->ramcfg_10_02_10 = (nvbios_rd08(bios, data + 0x02) & 0x10) >> 4;
		p->ramcfg_10_02_20 = (nvbios_rd08(bios, data + 0x02) & 0x20) >> 5;
		p->ramcfg_DLLoff   = (nvbios_rd08(bios, data + 0x02) & 0x40) >> 6;
		p->ramcfg_10_03_0f = (nvbios_rd08(bios, data + 0x03) & 0x0f) >> 0;
		p->ramcfg_10_04_01 = (nvbios_rd08(bios, data + 0x04) & 0x01) >> 0;
		p->ramcfg_FBVDDQ   = (nvbios_rd08(bios, data + 0x04) & 0x08) >> 3;
		p->ramcfg_10_05    = (nvbios_rd08(bios, data + 0x05) & 0xff) >> 0;
		p->ramcfg_10_06    = (nvbios_rd08(bios, data + 0x06) & 0xff) >> 0;
		p->ramcfg_10_07    = (nvbios_rd08(bios, data + 0x07) & 0xff) >> 0;
		p->ramcfg_10_08    = (nvbios_rd08(bios, data + 0x08) & 0xff) >> 0;
		p->ramcfg_10_09_0f = (nvbios_rd08(bios, data + 0x09) & 0x0f) >> 0;
		p->ramcfg_10_09_f0 = (nvbios_rd08(bios, data + 0x09) & 0xf0) >> 4;
		break;
	case 0x11:
		p->ramcfg_timing   =  nvbios_rd08(bios, data + 0x00);
		p->ramcfg_11_01_01 = (nvbios_rd08(bios, data + 0x01) & 0x01) >> 0;
		p->ramcfg_11_01_02 = (nvbios_rd08(bios, data + 0x01) & 0x02) >> 1;
		p->ramcfg_11_01_04 = (nvbios_rd08(bios, data + 0x01) & 0x04) >> 2;
		p->ramcfg_11_01_08 = (nvbios_rd08(bios, data + 0x01) & 0x08) >> 3;
		p->ramcfg_11_01_10 = (nvbios_rd08(bios, data + 0x01) & 0x10) >> 4;
		p->ramcfg_DLLoff =   (nvbios_rd08(bios, data + 0x01) & 0x20) >> 5;
		p->ramcfg_11_01_40 = (nvbios_rd08(bios, data + 0x01) & 0x40) >> 6;
		p->ramcfg_11_01_80 = (nvbios_rd08(bios, data + 0x01) & 0x80) >> 7;
		p->ramcfg_11_02_03 = (nvbios_rd08(bios, data + 0x02) & 0x03) >> 0;
		p->ramcfg_11_02_04 = (nvbios_rd08(bios, data + 0x02) & 0x04) >> 2;
		p->ramcfg_11_02_08 = (nvbios_rd08(bios, data + 0x02) & 0x08) >> 3;
		p->ramcfg_11_02_10 = (nvbios_rd08(bios, data + 0x02) & 0x10) >> 4;
		p->ramcfg_11_02_40 = (nvbios_rd08(bios, data + 0x02) & 0x40) >> 6;
		p->ramcfg_11_02_80 = (nvbios_rd08(bios, data + 0x02) & 0x80) >> 7;
		p->ramcfg_11_03_0f = (nvbios_rd08(bios, data + 0x03) & 0x0f) >> 0;
		p->ramcfg_11_03_30 = (nvbios_rd08(bios, data + 0x03) & 0x30) >> 4;
		p->ramcfg_11_03_c0 = (nvbios_rd08(bios, data + 0x03) & 0xc0) >> 6;
		p->ramcfg_11_03_f0 = (nvbios_rd08(bios, data + 0x03) & 0xf0) >> 4;
		p->ramcfg_11_04    = (nvbios_rd08(bios, data + 0x04) & 0xff) >> 0;
		p->ramcfg_11_06    = (nvbios_rd08(bios, data + 0x06) & 0xff) >> 0;
		p->ramcfg_11_07_02 = (nvbios_rd08(bios, data + 0x07) & 0x02) >> 1;
		p->ramcfg_11_07_04 = (nvbios_rd08(bios, data + 0x07) & 0x04) >> 2;
		p->ramcfg_11_07_08 = (nvbios_rd08(bios, data + 0x07) & 0x08) >> 3;
		p->ramcfg_11_07_10 = (nvbios_rd08(bios, data + 0x07) & 0x10) >> 4;
		p->ramcfg_11_07_40 = (nvbios_rd08(bios, data + 0x07) & 0x40) >> 6;
		p->ramcfg_11_07_80 = (nvbios_rd08(bios, data + 0x07) & 0x80) >> 7;
		p->ramcfg_11_08_01 = (nvbios_rd08(bios, data + 0x08) & 0x01) >> 0;
		p->ramcfg_11_08_02 = (nvbios_rd08(bios, data + 0x08) & 0x02) >> 1;
		p->ramcfg_11_08_04 = (nvbios_rd08(bios, data + 0x08) & 0x04) >> 2;
		p->ramcfg_11_08_08 = (nvbios_rd08(bios, data + 0x08) & 0x08) >> 3;
		p->ramcfg_11_08_10 = (nvbios_rd08(bios, data + 0x08) & 0x10) >> 4;
		p->ramcfg_11_08_20 = (nvbios_rd08(bios, data + 0x08) & 0x20) >> 5;
		p->ramcfg_11_09    = (nvbios_rd08(bios, data + 0x09) & 0xff) >> 0;
		break;
	default:
		data = 0;
		break;
	}
	return data;
}