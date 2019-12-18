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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gk104_ibus_intr_gpc (struct nvkm_subdev*,int) ; 
 int /*<<< orphan*/  gk104_ibus_intr_hub (struct nvkm_subdev*,int) ; 
 int /*<<< orphan*/  gk104_ibus_intr_rop (struct nvkm_subdev*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

void
gk104_ibus_intr(struct nvkm_subdev *ibus)
{
	struct nvkm_device *device = ibus->device;
	u32 intr0 = nvkm_rd32(device, 0x120058);
	u32 intr1 = nvkm_rd32(device, 0x12005c);
	u32 hubnr = nvkm_rd32(device, 0x120070);
	u32 ropnr = nvkm_rd32(device, 0x120074);
	u32 gpcnr = nvkm_rd32(device, 0x120078);
	u32 i;

	for (i = 0; (intr0 & 0x0000ff00) && i < hubnr; i++) {
		u32 stat = 0x00000100 << i;
		if (intr0 & stat) {
			gk104_ibus_intr_hub(ibus, i);
			intr0 &= ~stat;
		}
	}

	for (i = 0; (intr0 & 0xffff0000) && i < ropnr; i++) {
		u32 stat = 0x00010000 << i;
		if (intr0 & stat) {
			gk104_ibus_intr_rop(ibus, i);
			intr0 &= ~stat;
		}
	}

	for (i = 0; intr1 && i < gpcnr; i++) {
		u32 stat = 0x00000001 << i;
		if (intr1 & stat) {
			gk104_ibus_intr_gpc(ibus, i);
			intr1 &= ~stat;
		}
	}
}