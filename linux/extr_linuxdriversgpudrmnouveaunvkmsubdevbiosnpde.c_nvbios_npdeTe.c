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
typedef  int u32 ;
typedef  int u16 ;
struct nvkm_bios {int /*<<< orphan*/  subdev; } ;
struct nvbios_pcirT {int dummy; } ;

/* Variables and functions */
 int nvbios_pcirTp (struct nvkm_bios*,int,int /*<<< orphan*/ *,int*,struct nvbios_pcirT*) ; 
 int nvbios_rd32 (struct nvkm_bios*,int) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,int,int) ; 

u32
nvbios_npdeTe(struct nvkm_bios *bios, u32 base)
{
	struct nvbios_pcirT pcir;
	u8  ver; u16 hdr;
	u32 data = nvbios_pcirTp(bios, base, &ver, &hdr, &pcir);
	if (data = (data + hdr + 0x0f) & ~0x0f, data) {
		switch (nvbios_rd32(bios, data + 0x00)) {
		case 0x4544504e: /* NPDE */
			break;
		default:
			nvkm_debug(&bios->subdev,
				   "%08x: NPDE signature (%08x) unknown\n",
				   data, nvbios_rd32(bios, data + 0x00));
			data = 0;
			break;
		}
	}
	return data;
}