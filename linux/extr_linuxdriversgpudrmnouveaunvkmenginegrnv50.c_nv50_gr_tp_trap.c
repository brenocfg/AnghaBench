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
 int /*<<< orphan*/  nv50_gr_mp_trap (struct nv50_gr*,int,int) ; 
 int /*<<< orphan*/  nv50_gr_prop_trap (struct nv50_gr*,int,int,int) ; 
 int /*<<< orphan*/  nv50_mpc_traps ; 
 int /*<<< orphan*/  nv50_tex_traps ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,...) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_snprintbf (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,char const*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
nv50_gr_tp_trap(struct nv50_gr *gr, int type, u32 ustatus_old,
		  u32 ustatus_new, int display, const char *name)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 units = nvkm_rd32(device, 0x1540);
	int tps = 0;
	int i, r;
	char msg[128];
	u32 ustatus_addr, ustatus;
	for (i = 0; i < 16; i++) {
		if (!(units & (1 << i)))
			continue;
		if (device->chipset < 0xa0)
			ustatus_addr = ustatus_old + (i << 12);
		else
			ustatus_addr = ustatus_new + (i << 11);
		ustatus = nvkm_rd32(device, ustatus_addr) & 0x7fffffff;
		if (!ustatus)
			continue;
		tps++;
		switch (type) {
		case 6: /* texture error... unknown for now */
			if (display) {
				nvkm_error(subdev, "magic set %d:\n", i);
				for (r = ustatus_addr + 4; r <= ustatus_addr + 0x10; r += 4)
					nvkm_error(subdev, "\t%08x: %08x\n", r,
						   nvkm_rd32(device, r));
				if (ustatus) {
					nvkm_snprintbf(msg, sizeof(msg),
						       nv50_tex_traps, ustatus);
					nvkm_error(subdev,
						   "%s - TP%d: %08x [%s]\n",
						   name, i, ustatus, msg);
					ustatus = 0;
				}
			}
			break;
		case 7: /* MP error */
			if (ustatus & 0x04030000) {
				nv50_gr_mp_trap(gr, i, display);
				ustatus &= ~0x04030000;
			}
			if (ustatus && display) {
				nvkm_snprintbf(msg, sizeof(msg),
					       nv50_mpc_traps, ustatus);
				nvkm_error(subdev, "%s - TP%d: %08x [%s]\n",
					   name, i, ustatus, msg);
				ustatus = 0;
			}
			break;
		case 8: /* PROP error */
			if (display)
				nv50_gr_prop_trap(
						gr, ustatus_addr, ustatus, i);
			ustatus = 0;
			break;
		}
		if (ustatus) {
			if (display)
				nvkm_error(subdev, "%s - TP%d: Unhandled ustatus %08x\n", name, i, ustatus);
		}
		nvkm_wr32(device, ustatus_addr, 0xc0000000);
	}

	if (!tps && display)
		nvkm_warn(subdev, "%s - No TPs claiming errors?\n", name);
}