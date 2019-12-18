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
typedef  scalar_t__ u32 ;
struct nvkm_memory {int dummy; } ;
struct TYPE_4__ {int chid; TYPE_1__* inst; } ;
struct gk104_fifo_chan {TYPE_2__ base; } ;
struct TYPE_3__ {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_memory*,scalar_t__,int) ; 

__attribute__((used)) static void
gm107_fifo_runlist_chan(struct gk104_fifo_chan *chan,
			struct nvkm_memory *memory, u32 offset)
{
	nvkm_wo32(memory, offset + 0, chan->base.chid);
	nvkm_wo32(memory, offset + 4, chan->base.inst->addr >> 12);
}