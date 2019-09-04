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
typedef  scalar_t__ u64 ;
struct nvkm_gpuobj {scalar_t__ addr; scalar_t__ size; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_2__ {size_t index; } ;
struct nvkm_engine {TYPE_1__ subdev; } ;
struct nv50_fifo_chan {int /*<<< orphan*/  eng; struct nvkm_gpuobj** engn; } ;

/* Variables and functions */
 int g84_fifo_chan_engine_addr (struct nvkm_engine*) ; 
 int lower_32_bits (scalar_t__) ; 
 struct nv50_fifo_chan* nv50_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wo32 (int /*<<< orphan*/ ,int,int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int
g84_fifo_chan_engine_init(struct nvkm_fifo_chan *base,
			  struct nvkm_engine *engine)
{
	struct nv50_fifo_chan *chan = nv50_fifo_chan(base);
	struct nvkm_gpuobj *engn = chan->engn[engine->subdev.index];
	u64 limit, start;
	int offset;

	offset = g84_fifo_chan_engine_addr(engine);
	if (offset < 0)
		return 0;
	limit = engn->addr + engn->size - 1;
	start = engn->addr;

	nvkm_kmap(chan->eng);
	nvkm_wo32(chan->eng, offset + 0x00, 0x00190000);
	nvkm_wo32(chan->eng, offset + 0x04, lower_32_bits(limit));
	nvkm_wo32(chan->eng, offset + 0x08, lower_32_bits(start));
	nvkm_wo32(chan->eng, offset + 0x0c, upper_32_bits(limit) << 24 |
					    upper_32_bits(start));
	nvkm_wo32(chan->eng, offset + 0x10, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x14, 0x00000000);
	nvkm_done(chan->eng);
	return 0;
}