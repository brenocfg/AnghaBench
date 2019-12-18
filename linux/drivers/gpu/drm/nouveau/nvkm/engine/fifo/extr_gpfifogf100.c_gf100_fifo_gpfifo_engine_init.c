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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct nvkm_gpuobj {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_8__ {size_t index; } ;
struct nvkm_engine {TYPE_4__ subdev; } ;
struct TYPE_5__ {struct nvkm_gpuobj* inst; } ;
struct gf100_fifo_chan {TYPE_3__* engn; TYPE_1__ base; } ;
struct TYPE_7__ {TYPE_2__* vma; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 struct gf100_fifo_chan* gf100_fifo_chan (struct nvkm_fifo_chan*) ; 
 scalar_t__ gf100_fifo_gpfifo_engine_addr (struct nvkm_engine*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_gpuobj*,scalar_t__ const,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gf100_fifo_gpfifo_engine_init(struct nvkm_fifo_chan *base,
			      struct nvkm_engine *engine)
{
	const u32 offset = gf100_fifo_gpfifo_engine_addr(engine);
	struct gf100_fifo_chan *chan = gf100_fifo_chan(base);
	struct nvkm_gpuobj *inst = chan->base.inst;

	if (offset) {
		u64 addr = chan->engn[engine->subdev.index].vma->addr;
		nvkm_kmap(inst);
		nvkm_wo32(inst, offset + 0x00, lower_32_bits(addr) | 4);
		nvkm_wo32(inst, offset + 0x04, upper_32_bits(addr));
		nvkm_done(inst);
	}

	return 0;
}