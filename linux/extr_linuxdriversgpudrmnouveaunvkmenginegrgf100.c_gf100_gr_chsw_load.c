#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_gr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gf100_gr {TYPE_3__ base; int /*<<< orphan*/  firmware; } ;

/* Variables and functions */
 struct gf100_gr* gf100_gr (struct nvkm_gr*) ; 
 int nvkm_rd32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
gf100_gr_chsw_load(struct nvkm_gr *base)
{
	struct gf100_gr *gr = gf100_gr(base);
	if (!gr->firmware) {
		u32 trace = nvkm_rd32(gr->base.engine.subdev.device, 0x40981c);
		if (trace & 0x00000040)
			return true;
	} else {
		u32 mthd = nvkm_rd32(gr->base.engine.subdev.device, 0x409808);
		if (mthd & 0x00080000)
			return true;
	}
	return false;
}