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
struct nvkm_device {int chipset; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct nv50_gr {TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  nv50_mp_exec_errors ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,...) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_snprintbf (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv50_gr_mp_trap(struct nv50_gr *gr, int tpid, int display)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 units = nvkm_rd32(device, 0x1540);
	u32 addr, mp10, status, pc, oplow, ophigh;
	char msg[128];
	int i;
	int mps = 0;
	for (i = 0; i < 4; i++) {
		if (!(units & 1 << (i+24)))
			continue;
		if (device->chipset < 0xa0)
			addr = 0x408200 + (tpid << 12) + (i << 7);
		else
			addr = 0x408100 + (tpid << 11) + (i << 7);
		mp10 = nvkm_rd32(device, addr + 0x10);
		status = nvkm_rd32(device, addr + 0x14);
		if (!status)
			continue;
		if (display) {
			nvkm_rd32(device, addr + 0x20);
			pc = nvkm_rd32(device, addr + 0x24);
			oplow = nvkm_rd32(device, addr + 0x70);
			ophigh = nvkm_rd32(device, addr + 0x74);
			nvkm_snprintbf(msg, sizeof(msg),
				       nv50_mp_exec_errors, status);
			nvkm_error(subdev, "TRAP_MP_EXEC - TP %d MP %d: "
					   "%08x [%s] at %06x warp %d, "
					   "opcode %08x %08x\n",
				   tpid, i, status, msg, pc & 0xffffff,
				   pc >> 24, oplow, ophigh);
		}
		nvkm_wr32(device, addr + 0x10, mp10);
		nvkm_wr32(device, addr + 0x14, 0);
		mps++;
	}
	if (!mps && display)
		nvkm_error(subdev, "TRAP_MP_EXEC - TP %d: "
				"No MPs claiming errors?\n", tpid);
}