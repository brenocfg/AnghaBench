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
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gf100_gr {TYPE_3__ base; scalar_t__ firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (int /*<<< orphan*/ ,int,int const) ; 

void
gf100_gr_init_fecs_exceptions(struct gf100_gr *gr)
{
	const u32 data = gr->firmware ? 0x000e0000 : 0x000e0001;
	nvkm_wr32(gr->base.engine.subdev.device, 0x409c24, data);
}