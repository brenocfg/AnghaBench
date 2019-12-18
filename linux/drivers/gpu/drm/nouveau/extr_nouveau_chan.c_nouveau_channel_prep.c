#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_17__ {scalar_t__ client; } ;
struct TYPE_24__ {scalar_t__ family; scalar_t__ ram_user; } ;
struct nvif_device {TYPE_10__ object; TYPE_4__ info; } ;
struct nv_dma_v0 {scalar_t__ limit; scalar_t__ start; void* access; void* target; } ;
struct TYPE_25__ {scalar_t__ size; scalar_t__ base; scalar_t__ bridge; } ;
struct nouveau_drm {TYPE_5__ agp; } ;
struct TYPE_26__ {scalar_t__ limit; } ;
struct TYPE_19__ {TYPE_6__ vmm; int /*<<< orphan*/  cli; } ;
struct nouveau_cli {TYPE_12__ vmm; TYPE_12__ svm; } ;
struct TYPE_27__ {int /*<<< orphan*/  ctxdma; TYPE_11__* buffer; TYPE_13__* vma; int /*<<< orphan*/  addr; } ;
struct nouveau_channel {TYPE_7__ push; TYPE_12__* vmm; struct nouveau_drm* drm; int /*<<< orphan*/  killed; struct nvif_device* device; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_28__ {TYPE_3__* func; } ;
struct TYPE_23__ {scalar_t__ (* resource_addr ) (TYPE_8__*,int) ;} ;
struct TYPE_21__ {scalar_t__ mem_type; } ;
struct TYPE_22__ {TYPE_1__ mem; int /*<<< orphan*/  offset; } ;
struct TYPE_20__ {int /*<<< orphan*/  addr; } ;
struct TYPE_18__ {TYPE_2__ bo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NV_DEVICE_INFO_V0_FERMI ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 scalar_t__ NV_DEVICE_INFO_V0_TNT ; 
 int /*<<< orphan*/  NV_DMA_FROM_MEMORY ; 
 void* NV_DMA_V0_ACCESS_RDWR ; 
 void* NV_DMA_V0_ACCESS_VM ; 
 void* NV_DMA_V0_TARGET_AGP ; 
 void* NV_DMA_V0_TARGET_PCI ; 
 void* NV_DMA_V0_TARGET_VM ; 
 void* NV_DMA_V0_TARGET_VRAM ; 
 int TTM_PL_FLAG_TT ; 
 int TTM_PL_FLAG_UNCACHED ; 
 int TTM_PL_FLAG_VRAM ; 
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nouveau_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nouveau_bo_map (TYPE_11__*) ; 
 int nouveau_bo_new (struct nouveau_cli*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_11__**) ; 
 int nouveau_bo_pin (TYPE_11__*,int,int) ; 
 int /*<<< orphan*/  nouveau_channel_del (struct nouveau_channel**) ; 
 int nouveau_vma_new (TYPE_11__*,TYPE_12__*,TYPE_13__**) ; 
 scalar_t__ nouveau_vram_pushbuf ; 
 int nvif_object_init (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nv_dma_v0*,int,int /*<<< orphan*/ *) ; 
 TYPE_8__* nvxx_device (struct nvif_device*) ; 
 scalar_t__ stub1 (TYPE_8__*,int) ; 

__attribute__((used)) static int
nouveau_channel_prep(struct nouveau_drm *drm, struct nvif_device *device,
		     u32 size, struct nouveau_channel **pchan)
{
	struct nouveau_cli *cli = (void *)device->object.client;
	struct nv_dma_v0 args = {};
	struct nouveau_channel *chan;
	u32 target;
	int ret;

	chan = *pchan = kzalloc(sizeof(*chan), GFP_KERNEL);
	if (!chan)
		return -ENOMEM;

	chan->device = device;
	chan->drm = drm;
	chan->vmm = cli->svm.cli ? &cli->svm : &cli->vmm;
	atomic_set(&chan->killed, 0);

	/* allocate memory for dma push buffer */
	target = TTM_PL_FLAG_TT | TTM_PL_FLAG_UNCACHED;
	if (nouveau_vram_pushbuf)
		target = TTM_PL_FLAG_VRAM;

	ret = nouveau_bo_new(cli, size, 0, target, 0, 0, NULL, NULL,
			    &chan->push.buffer);
	if (ret == 0) {
		ret = nouveau_bo_pin(chan->push.buffer, target, false);
		if (ret == 0)
			ret = nouveau_bo_map(chan->push.buffer);
	}

	if (ret) {
		nouveau_channel_del(pchan);
		return ret;
	}

	/* create dma object covering the *entire* memory space that the
	 * pushbuf lives in, this is because the GEM code requires that
	 * we be able to call out to other (indirect) push buffers
	 */
	chan->push.addr = chan->push.buffer->bo.offset;

	if (device->info.family >= NV_DEVICE_INFO_V0_TESLA) {
		ret = nouveau_vma_new(chan->push.buffer, chan->vmm,
				      &chan->push.vma);
		if (ret) {
			nouveau_channel_del(pchan);
			return ret;
		}

		chan->push.addr = chan->push.vma->addr;

		if (device->info.family >= NV_DEVICE_INFO_V0_FERMI)
			return 0;

		args.target = NV_DMA_V0_TARGET_VM;
		args.access = NV_DMA_V0_ACCESS_VM;
		args.start = 0;
		args.limit = chan->vmm->vmm.limit - 1;
	} else
	if (chan->push.buffer->bo.mem.mem_type == TTM_PL_VRAM) {
		if (device->info.family == NV_DEVICE_INFO_V0_TNT) {
			/* nv04 vram pushbuf hack, retarget to its location in
			 * the framebuffer bar rather than direct vram access..
			 * nfi why this exists, it came from the -nv ddx.
			 */
			args.target = NV_DMA_V0_TARGET_PCI;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = nvxx_device(device)->func->
				resource_addr(nvxx_device(device), 1);
			args.limit = args.start + device->info.ram_user - 1;
		} else {
			args.target = NV_DMA_V0_TARGET_VRAM;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = 0;
			args.limit = device->info.ram_user - 1;
		}
	} else {
		if (chan->drm->agp.bridge) {
			args.target = NV_DMA_V0_TARGET_AGP;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = chan->drm->agp.base;
			args.limit = chan->drm->agp.base +
				     chan->drm->agp.size - 1;
		} else {
			args.target = NV_DMA_V0_TARGET_VM;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = 0;
			args.limit = chan->vmm->vmm.limit - 1;
		}
	}

	ret = nvif_object_init(&device->object, 0, NV_DMA_FROM_MEMORY,
			       &args, sizeof(args), &chan->push.ctxdma);
	if (ret) {
		nouveau_channel_del(pchan);
		return ret;
	}

	return 0;
}