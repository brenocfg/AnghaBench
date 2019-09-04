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
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct nv50_gr {TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  nv50_gr_trap_prop ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,int,...) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_snprintbf (char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nv50_gr_prop_trap(struct nv50_gr *gr, u32 ustatus_addr, u32 ustatus, u32 tp)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 e0c = nvkm_rd32(device, ustatus_addr + 0x04);
	u32 e10 = nvkm_rd32(device, ustatus_addr + 0x08);
	u32 e14 = nvkm_rd32(device, ustatus_addr + 0x0c);
	u32 e18 = nvkm_rd32(device, ustatus_addr + 0x10);
	u32 e1c = nvkm_rd32(device, ustatus_addr + 0x14);
	u32 e20 = nvkm_rd32(device, ustatus_addr + 0x18);
	u32 e24 = nvkm_rd32(device, ustatus_addr + 0x1c);
	char msg[128];

	/* CUDA memory: l[], g[] or stack. */
	if (ustatus & 0x00000080) {
		if (e18 & 0x80000000) {
			/* g[] read fault? */
			nvkm_error(subdev, "TRAP_PROP - TP %d - CUDA_FAULT - Global read fault at address %02x%08x\n",
					 tp, e14, e10 | ((e18 >> 24) & 0x1f));
			e18 &= ~0x1f000000;
		} else if (e18 & 0xc) {
			/* g[] write fault? */
			nvkm_error(subdev, "TRAP_PROP - TP %d - CUDA_FAULT - Global write fault at address %02x%08x\n",
				 tp, e14, e10 | ((e18 >> 7) & 0x1f));
			e18 &= ~0x00000f80;
		} else {
			nvkm_error(subdev, "TRAP_PROP - TP %d - Unknown CUDA fault at address %02x%08x\n",
				 tp, e14, e10);
		}
		ustatus &= ~0x00000080;
	}
	if (ustatus) {
		nvkm_snprintbf(msg, sizeof(msg), nv50_gr_trap_prop, ustatus);
		nvkm_error(subdev, "TRAP_PROP - TP %d - %08x [%s] - "
				   "Address %02x%08x\n",
			   tp, ustatus, msg, e14, e10);
	}
	nvkm_error(subdev, "TRAP_PROP - TP %d - e0c: %08x, e18: %08x, e1c: %08x, e20: %08x, e24: %08x\n",
		 tp, e0c, e18, e1c, e20, e24);
}