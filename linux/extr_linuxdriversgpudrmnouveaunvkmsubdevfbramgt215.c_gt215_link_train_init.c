#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_device {struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_M0205E {int type; } ;
struct gt215_ltrain {void* r_111400; void* r_1111e0; void* r_100720; int /*<<< orphan*/  memory; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {TYPE_2__* fb; } ;
struct gt215_ram {struct gt215_ltrain ltrain; TYPE_3__ base; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NVA3_TRAIN_ONCE ; 
 int /*<<< orphan*/  NVA3_TRAIN_UNSUPPORTED ; 
 int /*<<< orphan*/  NVKM_RAM_MM_NORMAL ; 
 int /*<<< orphan*/  nvbios_M0205Ep (struct nvkm_bios*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_M0205E*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_memory_addr (int /*<<< orphan*/ ) ; 
 int nvkm_ram_get (struct nvkm_device*,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 void* nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int const) ; 

__attribute__((used)) static int
gt215_link_train_init(struct gt215_ram *ram)
{
	static const u32 pattern[16] = {
		0xaaaaaaaa, 0xcccccccc, 0xdddddddd, 0xeeeeeeee,
		0x00000000, 0x11111111, 0x44444444, 0xdddddddd,
		0x33333333, 0x55555555, 0x77777777, 0x66666666,
		0x99999999, 0x88888888, 0xeeeeeeee, 0xbbbbbbbb,
	};
	struct gt215_ltrain *train = &ram->ltrain;
	struct nvkm_device *device = ram->base.fb->subdev.device;
	struct nvkm_bios *bios = device->bios;
	struct nvbios_M0205E M0205E;
	u8 ver, hdr, cnt, len;
	u32 r001700;
	u64 addr;
	int ret, i = 0;

	train->state = NVA3_TRAIN_UNSUPPORTED;

	/* We support type "5"
	 * XXX: training pattern table appears to be unused for this routine */
	if (!nvbios_M0205Ep(bios, i, &ver, &hdr, &cnt, &len, &M0205E))
		return -ENOENT;

	if (M0205E.type != 5)
		return 0;

	train->state = NVA3_TRAIN_ONCE;

	ret = nvkm_ram_get(device, NVKM_RAM_MM_NORMAL, 0x01, 16, 0x8000,
			   true, true, &ram->ltrain.memory);
	if (ret)
		return ret;

	addr = nvkm_memory_addr(ram->ltrain.memory);

	nvkm_wr32(device, 0x100538, 0x10000000 | (addr >> 16));
	nvkm_wr32(device, 0x1005a8, 0x0000ffff);
	nvkm_mask(device, 0x10f800, 0x00000001, 0x00000001);

	for (i = 0; i < 0x30; i++) {
		nvkm_wr32(device, 0x10f8c0, (i << 8) | i);
		nvkm_wr32(device, 0x10f900, pattern[i % 16]);
	}

	for (i = 0; i < 0x30; i++) {
		nvkm_wr32(device, 0x10f8e0, (i << 8) | i);
		nvkm_wr32(device, 0x10f920, pattern[i % 16]);
	}

	/* And upload the pattern */
	r001700 = nvkm_rd32(device, 0x1700);
	nvkm_wr32(device, 0x1700, addr >> 16);
	for (i = 0; i < 16; i++)
		nvkm_wr32(device, 0x700000 + (i << 2), pattern[i]);
	for (i = 0; i < 16; i++)
		nvkm_wr32(device, 0x700100 + (i << 2), pattern[i]);
	nvkm_wr32(device, 0x1700, r001700);

	train->r_100720 = nvkm_rd32(device, 0x100720);
	train->r_1111e0 = nvkm_rd32(device, 0x1111e0);
	train->r_111400 = nvkm_rd32(device, 0x111400);
	return 0;
}