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
struct nvkm_devinit {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nv50_devinit {int r001540; TYPE_2__ base; } ;

/* Variables and functions */
 int* gt215_devinit_mmio_part ; 
 int hweight8 (int) ; 
 struct nv50_devinit* nv50_devinit (struct nvkm_devinit*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static u32
gt215_devinit_mmio(struct nvkm_devinit *base, u32 addr)
{
	struct nv50_devinit *init = nv50_devinit(base);
	struct nvkm_device *device = init->base.subdev.device;
	u32 *mmio = gt215_devinit_mmio_part;

	/* the init tables on some boards have INIT_RAM_RESTRICT_ZM_REG_GROUP
	 * instructions which touch registers that may not even exist on
	 * some configurations (Quadro 400), which causes the register
	 * interface to screw up for some amount of time after attempting to
	 * write to one of these, and results in all sorts of things going
	 * horribly wrong.
	 *
	 * the binary driver avoids touching these registers at all, however,
	 * the video bios doesn't care and does what the scripts say.  it's
	 * presumed that the io-port access to init registers isn't effected
	 * by the screw-up bug mentioned above.
	 *
	 * really, a new opcode should've been invented to handle these
	 * requirements, but whatever, it's too late for that now.
	 */
	while (mmio[0]) {
		if (addr >= mmio[0] && addr <= mmio[1]) {
			u32 part = (addr / mmio[2]) & 7;
			if (!init->r001540)
				init->r001540 = nvkm_rd32(device, 0x001540);
			if (part >= hweight8((init->r001540 >> 16) & 0xff))
				return ~0;
			return addr;
		}
		mmio += 3;
	}

	return addr;
}