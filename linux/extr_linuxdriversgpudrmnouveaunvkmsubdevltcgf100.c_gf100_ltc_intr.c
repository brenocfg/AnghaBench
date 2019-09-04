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
 int /*<<< orphan*/  gf100_ltc_lts_intr (struct nvkm_ltc*,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

void
gf100_ltc_intr(struct nvkm_ltc *ltc)
{
	struct nvkm_device *device = ltc->subdev.device;
	u32 mask;

	mask = nvkm_rd32(device, 0x00017c);
	while (mask) {
		u32 s, c = __ffs(mask);
		for (s = 0; s < ltc->lts_nr; s++)
			gf100_ltc_lts_intr(ltc, c, s);
		mask &= ~(1 << c);
	}
}