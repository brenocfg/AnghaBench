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
typedef  int u32 ;
struct nvkm_gpuobj {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_7__ {size_t index; } ;
struct nvkm_engine {TYPE_3__ subdev; } ;
struct TYPE_8__ {struct nvkm_gpuobj* inst; } ;
struct gk104_fifo_chan {TYPE_2__* engn; TYPE_4__ base; } ;
struct TYPE_6__ {TYPE_1__* vma; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 struct gk104_fifo_chan* gk104_fifo_chan (struct nvkm_fifo_chan*) ; 
 int gk104_fifo_gpfifo_engine_addr (struct nvkm_engine*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_gpuobj*,int,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gk104_fifo_gpfifo_engine_init(struct nvkm_fifo_chan *base,
			      struct nvkm_engine *engine)
{
	struct gk104_fifo_chan *chan = gk104_fifo_chan(base);
	struct nvkm_gpuobj *inst = chan->base.inst;
	u32 offset = gk104_fifo_gpfifo_engine_addr(engine);

	if (offset) {
		u64   addr = chan->engn[engine->subdev.index].vma->addr;
		u32 datalo = lower_32_bits(addr) | 0x00000004;
		u32 datahi = upper_32_bits(addr);
		nvkm_kmap(inst);
		nvkm_wo32(inst, (offset & 0xffff) + 0x00, datalo);
		nvkm_wo32(inst, (offset & 0xffff) + 0x04, datahi);
		if ((offset >>= 16)) {
			nvkm_wo32(inst, offset + 0x00, datalo);
			nvkm_wo32(inst, offset + 0x04, datahi);
		}
		nvkm_done(inst);
	}

	return 0;
}