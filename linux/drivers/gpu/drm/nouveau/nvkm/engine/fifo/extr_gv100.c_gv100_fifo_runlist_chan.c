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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct nvkm_memory {int dummy; } ;
struct TYPE_6__ {int chid; TYPE_1__* inst; } ;
struct gk104_fifo_chan {TYPE_2__ base; TYPE_4__* fifo; } ;
struct TYPE_7__ {struct nvkm_memory* mem; } ;
struct TYPE_8__ {TYPE_3__ user; } ;
struct TYPE_5__ {scalar_t__ addr; } ;

/* Variables and functions */
 int lower_32_bits (scalar_t__ const) ; 
 scalar_t__ nvkm_memory_addr (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_memory*,scalar_t__,int) ; 
 int upper_32_bits (scalar_t__ const) ; 

void
gv100_fifo_runlist_chan(struct gk104_fifo_chan *chan,
			struct nvkm_memory *memory, u32 offset)
{
	struct nvkm_memory *usermem = chan->fifo->user.mem;
	const u64 user = nvkm_memory_addr(usermem) + (chan->base.chid * 0x200);
	const u64 inst = chan->base.inst->addr;

	nvkm_wo32(memory, offset + 0x0, lower_32_bits(user));
	nvkm_wo32(memory, offset + 0x4, upper_32_bits(user));
	nvkm_wo32(memory, offset + 0x8, lower_32_bits(inst) | chan->base.chid);
	nvkm_wo32(memory, offset + 0xc, upper_32_bits(inst));
}