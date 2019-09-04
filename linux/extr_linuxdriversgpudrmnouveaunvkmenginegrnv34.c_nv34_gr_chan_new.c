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
struct nvkm_oclass {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_gr {int dummy; } ;
struct nvkm_fifo_chan {int chid; } ;
struct nv20_gr_chan {int chid; int /*<<< orphan*/  inst; struct nvkm_object object; struct nv20_gr* gr; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv20_gr {TYPE_3__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVKM_MEM_TARGET_INST ; 
 struct nv20_gr_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nv20_gr* nv20_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nv34_gr_chan ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 
 int nvkm_memory_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_wo32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
nv34_gr_chan_new(struct nvkm_gr *base, struct nvkm_fifo_chan *fifoch,
		 const struct nvkm_oclass *oclass, struct nvkm_object **pobject)
{
	struct nv20_gr *gr = nv20_gr(base);
	struct nv20_gr_chan *chan;
	int ret, i;

	if (!(chan = kzalloc(sizeof(*chan), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_object_ctor(&nv34_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fifoch->chid;
	*pobject = &chan->object;

	ret = nvkm_memory_new(gr->base.engine.subdev.device,
			      NVKM_MEM_TARGET_INST, 0x46dc, 16, true,
			      &chan->inst);
	if (ret)
		return ret;

	nvkm_kmap(chan->inst);
	nvkm_wo32(chan->inst, 0x0028, 0x00000001 | (chan->chid << 24));
	nvkm_wo32(chan->inst, 0x040c, 0x01000101);
	nvkm_wo32(chan->inst, 0x0420, 0x00000111);
	nvkm_wo32(chan->inst, 0x0424, 0x00000060);
	nvkm_wo32(chan->inst, 0x0440, 0x00000080);
	nvkm_wo32(chan->inst, 0x0444, 0xffff0000);
	nvkm_wo32(chan->inst, 0x0448, 0x00000001);
	nvkm_wo32(chan->inst, 0x045c, 0x44400000);
	nvkm_wo32(chan->inst, 0x0480, 0xffff0000);
	for (i = 0x04d4; i < 0x04dc; i += 4)
		nvkm_wo32(chan->inst, i, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x04e0, 0x00011100);
	for (i = 0x04fc; i < 0x053c; i += 4)
		nvkm_wo32(chan->inst, i, 0x07ff0000);
	nvkm_wo32(chan->inst, 0x0544, 0x4b7fffff);
	nvkm_wo32(chan->inst, 0x057c, 0x00000080);
	nvkm_wo32(chan->inst, 0x0580, 0x30201000);
	nvkm_wo32(chan->inst, 0x0584, 0x70605040);
	nvkm_wo32(chan->inst, 0x0588, 0xb8a89888);
	nvkm_wo32(chan->inst, 0x058c, 0xf8e8d8c8);
	nvkm_wo32(chan->inst, 0x05a0, 0xb0000000);
	for (i = 0x05f0; i < 0x0630; i += 4)
		nvkm_wo32(chan->inst, i, 0x00010588);
	for (i = 0x0630; i < 0x0670; i += 4)
		nvkm_wo32(chan->inst, i, 0x00030303);
	for (i = 0x06b0; i < 0x06f0; i += 4)
		nvkm_wo32(chan->inst, i, 0x0008aae4);
	for (i = 0x06f0; i < 0x0730; i += 4)
		nvkm_wo32(chan->inst, i, 0x01012000);
	for (i = 0x0730; i < 0x0770; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080008);
	nvkm_wo32(chan->inst, 0x0850, 0x00040000);
	nvkm_wo32(chan->inst, 0x0854, 0x00010000);
	for (i = 0x0858; i < 0x0868; i += 4)
		nvkm_wo32(chan->inst, i, 0x00040004);
	for (i = 0x15ac; i <= 0x271c ; i += 16) {
		nvkm_wo32(chan->inst, i + 0, 0x10700ff9);
		nvkm_wo32(chan->inst, i + 4, 0x0436086c);
		nvkm_wo32(chan->inst, i + 8, 0x000c001b);
	}
	for (i = 0x274c; i < 0x275c; i += 4)
		nvkm_wo32(chan->inst, i, 0x0000ffff);
	nvkm_wo32(chan->inst, 0x2ae0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2e9c, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2eb0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2edc, 0x40000000);
	nvkm_wo32(chan->inst, 0x2ee0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2ee4, 0x3f000000);
	nvkm_wo32(chan->inst, 0x2eec, 0x40000000);
	nvkm_wo32(chan->inst, 0x2ef0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2ef8, 0xbf800000);
	nvkm_wo32(chan->inst, 0x2f00, 0xbf800000);
	nvkm_done(chan->inst);
	return 0;
}