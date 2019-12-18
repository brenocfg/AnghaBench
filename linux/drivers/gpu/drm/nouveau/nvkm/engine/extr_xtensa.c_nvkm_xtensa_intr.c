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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct nvkm_xtensa {int addr; TYPE_2__* func; TYPE_1__ engine; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fifo_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int const) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int const,int) ; 
 struct nvkm_xtensa* nvkm_xtensa (struct nvkm_engine*) ; 

__attribute__((used)) static void
nvkm_xtensa_intr(struct nvkm_engine *engine)
{
	struct nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	struct nvkm_subdev *subdev = &xtensa->engine.subdev;
	struct nvkm_device *device = subdev->device;
	const u32 base = xtensa->addr;
	u32 unk104 = nvkm_rd32(device, base + 0xd04);
	u32 intr = nvkm_rd32(device, base + 0xc20);
	u32 chan = nvkm_rd32(device, base + 0xc28);
	u32 unk10c = nvkm_rd32(device, base + 0xd0c);

	if (intr & 0x10)
		nvkm_warn(subdev, "Watchdog interrupt, engine hung.\n");
	nvkm_wr32(device, base + 0xc20, intr);
	intr = nvkm_rd32(device, base + 0xc20);
	if (unk104 == 0x10001 && unk10c == 0x200 && chan && !intr) {
		nvkm_debug(subdev, "Enabling FIFO_CTRL\n");
		nvkm_mask(device, xtensa->addr + 0xd94, 0, xtensa->func->fifo_val);
	}
}