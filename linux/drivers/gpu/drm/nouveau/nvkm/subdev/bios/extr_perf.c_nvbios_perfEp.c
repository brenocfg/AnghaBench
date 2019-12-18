#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct nvkm_bios {TYPE_2__ subdev; } ;
struct nvbios_perfE {int pstate; int core; int memory; int fanspeed; int voltage; int shader; int script; int vdec; int disp; int pcie_width; int /*<<< orphan*/  pcie_speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_PCIE_SPEED_2_5 ; 
 int /*<<< orphan*/  NVKM_PCIE_SPEED_5_0 ; 
 int /*<<< orphan*/  NVKM_PCIE_SPEED_8_0 ; 
 int /*<<< orphan*/  memset (struct nvbios_perfE*,int,int) ; 
 scalar_t__ nvbios_perf_entry (struct nvkm_bios*,int,int*,int*,int*,int*) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_perfEp(struct nvkm_bios *bios, int idx,
	      u8 *ver, u8 *hdr, u8 *cnt, u8 *len, struct nvbios_perfE *info)
{
	u32 perf = nvbios_perf_entry(bios, idx, ver, hdr, cnt, len);
	memset(info, 0x00, sizeof(*info));
	info->pstate = nvbios_rd08(bios, perf + 0x00);
	switch (!!perf * *ver) {
	case 0x12:
	case 0x13:
	case 0x14:
		info->core     = nvbios_rd32(bios, perf + 0x01) * 10;
		info->memory   = nvbios_rd32(bios, perf + 0x05) * 20;
		info->fanspeed = nvbios_rd08(bios, perf + 0x37);
		if (*hdr > 0x38)
			info->voltage = nvbios_rd08(bios, perf + 0x38);
		break;
	case 0x21:
	case 0x23:
	case 0x24:
		info->fanspeed = nvbios_rd08(bios, perf + 0x04);
		info->voltage  = nvbios_rd08(bios, perf + 0x05);
		info->shader   = nvbios_rd16(bios, perf + 0x06) * 1000;
		info->core     = info->shader + (signed char)
				 nvbios_rd08(bios, perf + 0x08) * 1000;
		switch (bios->subdev.device->chipset) {
		case 0x49:
		case 0x4b:
			info->memory = nvbios_rd16(bios, perf + 0x0b) * 1000;
			break;
		default:
			info->memory = nvbios_rd16(bios, perf + 0x0b) * 2000;
			break;
		}
		break;
	case 0x25:
		info->fanspeed = nvbios_rd08(bios, perf + 0x04);
		info->voltage  = nvbios_rd08(bios, perf + 0x05);
		info->core     = nvbios_rd16(bios, perf + 0x06) * 1000;
		info->shader   = nvbios_rd16(bios, perf + 0x0a) * 1000;
		info->memory   = nvbios_rd16(bios, perf + 0x0c) * 1000;
		break;
	case 0x30:
		info->script   = nvbios_rd16(bios, perf + 0x02);
		/* fall through */
	case 0x35:
		info->fanspeed = nvbios_rd08(bios, perf + 0x06);
		info->voltage  = nvbios_rd08(bios, perf + 0x07);
		info->core     = nvbios_rd16(bios, perf + 0x08) * 1000;
		info->shader   = nvbios_rd16(bios, perf + 0x0a) * 1000;
		info->memory   = nvbios_rd16(bios, perf + 0x0c) * 1000;
		info->vdec     = nvbios_rd16(bios, perf + 0x10) * 1000;
		info->disp     = nvbios_rd16(bios, perf + 0x14) * 1000;
		break;
	case 0x40:
		info->voltage  = nvbios_rd08(bios, perf + 0x02);
		switch (nvbios_rd08(bios, perf + 0xb) & 0x3) {
		case 0:
			info->pcie_speed = NVKM_PCIE_SPEED_5_0;
			break;
		case 3:
		case 1:
			info->pcie_speed = NVKM_PCIE_SPEED_2_5;
			break;
		case 2:
			info->pcie_speed = NVKM_PCIE_SPEED_8_0;
			break;
		default:
			break;
		}
		info->pcie_width = 0xff;
		break;
	default:
		return 0;
	}
	return perf;
}