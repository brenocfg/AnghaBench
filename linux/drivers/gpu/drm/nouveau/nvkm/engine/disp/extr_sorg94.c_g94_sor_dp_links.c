#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int nr; int bw; scalar_t__ ef; } ;
struct nvkm_ior {TYPE_1__ dp; TYPE_4__* disp; } ;
struct nvkm_i2c_aux {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_2__ subdev; } ;
struct TYPE_8__ {TYPE_3__ engine; } ;

/* Variables and functions */
 int nv50_ior_base (struct nvkm_ior*) ; 
 int nv50_sor_link (struct nvkm_ior*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int const,int,int) ; 

int
g94_sor_dp_links(struct nvkm_ior *sor, struct nvkm_i2c_aux *aux)
{
	struct nvkm_device *device = sor->disp->engine.subdev.device;
	const u32 soff = nv50_ior_base(sor);
	const u32 loff = nv50_sor_link(sor);
	u32 dpctrl = 0x00000000;
	u32 clksor = 0x00000000;

	dpctrl |= ((1 << sor->dp.nr) - 1) << 16;
	if (sor->dp.ef)
		dpctrl |= 0x00004000;
	if (sor->dp.bw > 0x06)
		clksor |= 0x00040000;

	nvkm_mask(device, 0x614300 + soff, 0x000c0000, clksor);
	nvkm_mask(device, 0x61c10c + loff, 0x001f4000, dpctrl);
	return 0;
}