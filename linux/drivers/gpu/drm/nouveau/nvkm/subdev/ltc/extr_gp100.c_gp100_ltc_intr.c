#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_ltc {int lts_nr; TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int __ffs (int) ; 
 int /*<<< orphan*/  gm107_ltc_intr_lts (struct nvkm_ltc*,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

void
gp100_ltc_intr(struct nvkm_ltc *ltc)
{
	struct nvkm_device *device = ltc->subdev.device;
	u32 mask;

	mask = nvkm_rd32(device, 0x0001c0);
	while (mask) {
		u32 s, c = __ffs(mask);
		for (s = 0; s < ltc->lts_nr; s++)
			gm107_ltc_intr_lts(ltc, c, s);
		mask &= ~(1 << c);
	}
}