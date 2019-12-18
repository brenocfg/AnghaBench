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
struct gf100_gr {int gpc_nr; int rop_nr; TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  error ;

/* Variables and functions */
 int ROP_UNIT (int,int) ; 
 int /*<<< orphan*/  gf100_ccache_error ; 
 int /*<<< orphan*/  gf100_dispatch_error ; 
 int /*<<< orphan*/  gf100_gr_trap_gpc (struct gf100_gr*,int) ; 
 int /*<<< orphan*/  gf100_m2mf_error ; 
 int /*<<< orphan*/  gf100_macro_error ; 
 int /*<<< orphan*/  gf100_unk6_error ; 
 int /*<<< orphan*/  gk104_sked_error ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,...) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_snprintbf (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gf100_gr_trap_intr(struct gf100_gr *gr)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	char error[128];
	u32 trap = nvkm_rd32(device, 0x400108);
	int rop, gpc;

	if (trap & 0x00000001) {
		u32 stat = nvkm_rd32(device, 0x404000);

		nvkm_snprintbf(error, sizeof(error), gf100_dispatch_error,
			       stat & 0x3fffffff);
		nvkm_error(subdev, "DISPATCH %08x [%s]\n", stat, error);
		nvkm_wr32(device, 0x404000, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000001);
		trap &= ~0x00000001;
	}

	if (trap & 0x00000002) {
		u32 stat = nvkm_rd32(device, 0x404600);

		nvkm_snprintbf(error, sizeof(error), gf100_m2mf_error,
			       stat & 0x3fffffff);
		nvkm_error(subdev, "M2MF %08x [%s]\n", stat, error);

		nvkm_wr32(device, 0x404600, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000002);
		trap &= ~0x00000002;
	}

	if (trap & 0x00000008) {
		u32 stat = nvkm_rd32(device, 0x408030);

		nvkm_snprintbf(error, sizeof(error), gf100_ccache_error,
			       stat & 0x3fffffff);
		nvkm_error(subdev, "CCACHE %08x [%s]\n", stat, error);
		nvkm_wr32(device, 0x408030, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000008);
		trap &= ~0x00000008;
	}

	if (trap & 0x00000010) {
		u32 stat = nvkm_rd32(device, 0x405840);
		nvkm_error(subdev, "SHADER %08x, sph: 0x%06x, stage: 0x%02x\n",
			   stat, stat & 0xffffff, (stat >> 24) & 0x3f);
		nvkm_wr32(device, 0x405840, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000010);
		trap &= ~0x00000010;
	}

	if (trap & 0x00000040) {
		u32 stat = nvkm_rd32(device, 0x40601c);

		nvkm_snprintbf(error, sizeof(error), gf100_unk6_error,
			       stat & 0x3fffffff);
		nvkm_error(subdev, "UNK6 %08x [%s]\n", stat, error);

		nvkm_wr32(device, 0x40601c, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000040);
		trap &= ~0x00000040;
	}

	if (trap & 0x00000080) {
		u32 stat = nvkm_rd32(device, 0x404490);
		u32 pc = nvkm_rd32(device, 0x404494);
		u32 op = nvkm_rd32(device, 0x40449c);

		nvkm_snprintbf(error, sizeof(error), gf100_macro_error,
			       stat & 0x1fffffff);
		nvkm_error(subdev, "MACRO %08x [%s], pc: 0x%03x%s, op: 0x%08x\n",
			   stat, error, pc & 0x7ff,
			   (pc & 0x10000000) ? "" : " (invalid)",
			   op);

		nvkm_wr32(device, 0x404490, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000080);
		trap &= ~0x00000080;
	}

	if (trap & 0x00000100) {
		u32 stat = nvkm_rd32(device, 0x407020) & 0x3fffffff;

		nvkm_snprintbf(error, sizeof(error), gk104_sked_error, stat);
		nvkm_error(subdev, "SKED: %08x [%s]\n", stat, error);

		if (stat)
			nvkm_wr32(device, 0x407020, 0x40000000);
		nvkm_wr32(device, 0x400108, 0x00000100);
		trap &= ~0x00000100;
	}

	if (trap & 0x01000000) {
		u32 stat = nvkm_rd32(device, 0x400118);
		for (gpc = 0; stat && gpc < gr->gpc_nr; gpc++) {
			u32 mask = 0x00000001 << gpc;
			if (stat & mask) {
				gf100_gr_trap_gpc(gr, gpc);
				nvkm_wr32(device, 0x400118, mask);
				stat &= ~mask;
			}
		}
		nvkm_wr32(device, 0x400108, 0x01000000);
		trap &= ~0x01000000;
	}

	if (trap & 0x02000000) {
		for (rop = 0; rop < gr->rop_nr; rop++) {
			u32 statz = nvkm_rd32(device, ROP_UNIT(rop, 0x070));
			u32 statc = nvkm_rd32(device, ROP_UNIT(rop, 0x144));
			nvkm_error(subdev, "ROP%d %08x %08x\n",
				 rop, statz, statc);
			nvkm_wr32(device, ROP_UNIT(rop, 0x070), 0xc0000000);
			nvkm_wr32(device, ROP_UNIT(rop, 0x144), 0xc0000000);
		}
		nvkm_wr32(device, 0x400108, 0x02000000);
		trap &= ~0x02000000;
	}

	if (trap) {
		nvkm_error(subdev, "TRAP UNHANDLED %08x\n", trap);
		nvkm_wr32(device, 0x400108, trap);
	}
}