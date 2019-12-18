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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gf100_gr {TYPE_2__ base; } ;
struct bit_entry {int version; int length; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nvkm_bios*,char,struct bit_entry*) ; 
 int /*<<< orphan*/  nvbios_init (struct nvkm_subdev*,scalar_t__) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,scalar_t__) ; 

__attribute__((used)) static void
gm107_gr_init_bios_2(struct gf100_gr *gr)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_bios *bios = device->bios;
	struct bit_entry bit_P;
	if (!bit_entry(bios, 'P', &bit_P) &&
	    bit_P.version == 2 && bit_P.length >= 0x2c) {
		u32 data = nvbios_rd32(bios, bit_P.offset + 0x28);
		if (data) {
			u8 ver = nvbios_rd08(bios, data + 0x00);
			u8 hdr = nvbios_rd08(bios, data + 0x01);
			if (ver == 0x20 && hdr >= 8) {
				data = nvbios_rd32(bios, data + 0x04);
				if (data) {
					u32 save = nvkm_rd32(device, 0x619444);
					nvbios_init(subdev, data);
					nvkm_wr32(device, 0x619444, save);
				}
			}
		}
	}
}