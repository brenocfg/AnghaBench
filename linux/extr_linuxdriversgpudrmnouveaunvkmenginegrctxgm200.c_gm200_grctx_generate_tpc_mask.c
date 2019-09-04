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
typedef  size_t u32 ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct gf100_gr {size_t gpc_nr; int* tpc_nr; TYPE_3__ base; TYPE_4__* func; } ;
struct TYPE_8__ {size_t tpc_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (int /*<<< orphan*/ ,int,size_t) ; 

void
gm200_grctx_generate_tpc_mask(struct gf100_gr *gr)
{
	u32 tmp, i;
	for (tmp = 0, i = 0; i < gr->gpc_nr; i++)
		tmp |= ((1 << gr->tpc_nr[i]) - 1) << (i * gr->func->tpc_nr);
	nvkm_wr32(gr->base.engine.subdev.device, 0x4041c4, tmp);
}