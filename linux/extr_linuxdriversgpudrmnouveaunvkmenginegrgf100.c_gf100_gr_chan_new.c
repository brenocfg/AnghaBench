#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_oclass {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_gr {int dummy; } ;
struct nvkm_fifo_chan {int /*<<< orphan*/  vmm; } ;
struct nvkm_device {int dummy; } ;
struct gf100_vmm_map_v0 {int priv; } ;
struct gf100_gr_mmio {int size; int align; int priv; int addr; int data; size_t buffer; int shift; } ;
struct gf100_gr_data {int size; int align; int priv; int addr; int data; size_t buffer; int shift; } ;
struct gf100_gr_chan {int /*<<< orphan*/  mmio; int /*<<< orphan*/  mmio_nr; TYPE_4__* data; int /*<<< orphan*/  vmm; TYPE_5__* mmio_vma; struct nvkm_object object; struct gf100_gr* gr; } ;
struct TYPE_7__ {struct nvkm_device* device; } ;
struct TYPE_8__ {TYPE_1__ subdev; } ;
struct TYPE_9__ {TYPE_2__ engine; } ;
struct gf100_gr {struct gf100_gr_mmio* mmio_list; struct gf100_gr_mmio* mmio_data; TYPE_3__ base; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_11__ {int addr; } ;
struct TYPE_10__ {TYPE_5__* vma; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct gf100_gr_mmio*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVKM_MEM_TARGET_INST ; 
 struct gf100_gr* gf100_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  gf100_gr_chan ; 
 struct gf100_gr_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 
 int nvkm_memory_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,struct gf100_vmm_map_v0*,int) ; 
 int nvkm_memory_new (struct nvkm_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int nvkm_memory_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_object*) ; 
 int nvkm_vmm_get (int /*<<< orphan*/ ,int,int,TYPE_5__**) ; 
 int /*<<< orphan*/  nvkm_vmm_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wo32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
gf100_gr_chan_new(struct nvkm_gr *base, struct nvkm_fifo_chan *fifoch,
		  const struct nvkm_oclass *oclass,
		  struct nvkm_object **pobject)
{
	struct gf100_gr *gr = gf100_gr(base);
	struct gf100_gr_data *data = gr->mmio_data;
	struct gf100_gr_mmio *mmio = gr->mmio_list;
	struct gf100_gr_chan *chan;
	struct gf100_vmm_map_v0 args = { .priv = 1 };
	struct nvkm_device *device = gr->base.engine.subdev.device;
	int ret, i;

	if (!(chan = kzalloc(sizeof(*chan), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_object_ctor(&gf100_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->vmm = nvkm_vmm_ref(fifoch->vmm);
	*pobject = &chan->object;

	/* allocate memory for a "mmio list" buffer that's used by the HUB
	 * fuc to modify some per-context register settings on first load
	 * of the context.
	 */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x1000, 0x100,
			      false, &chan->mmio);
	if (ret)
		return ret;

	ret = nvkm_vmm_get(fifoch->vmm, 12, 0x1000, &chan->mmio_vma);
	if (ret)
		return ret;

	ret = nvkm_memory_map(chan->mmio, 0, fifoch->vmm,
			      chan->mmio_vma, &args, sizeof(args));
	if (ret)
		return ret;

	/* allocate buffers referenced by mmio list */
	for (i = 0; data->size && i < ARRAY_SIZE(gr->mmio_data); i++) {
		ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST,
				      data->size, data->align, false,
				      &chan->data[i].mem);
		if (ret)
			return ret;

		ret = nvkm_vmm_get(fifoch->vmm, 12,
				   nvkm_memory_size(chan->data[i].mem),
				   &chan->data[i].vma);
		if (ret)
			return ret;

		args.priv = data->priv;

		ret = nvkm_memory_map(chan->data[i].mem, 0, chan->vmm,
				      chan->data[i].vma, &args, sizeof(args));
		if (ret)
			return ret;

		data++;
	}

	/* finally, fill in the mmio list and point the context at it */
	nvkm_kmap(chan->mmio);
	for (i = 0; mmio->addr && i < ARRAY_SIZE(gr->mmio_list); i++) {
		u32 addr = mmio->addr;
		u32 data = mmio->data;

		if (mmio->buffer >= 0) {
			u64 info = chan->data[mmio->buffer].vma->addr;
			data |= info >> mmio->shift;
		}

		nvkm_wo32(chan->mmio, chan->mmio_nr++ * 4, addr);
		nvkm_wo32(chan->mmio, chan->mmio_nr++ * 4, data);
		mmio++;
	}
	nvkm_done(chan->mmio);
	return 0;
}