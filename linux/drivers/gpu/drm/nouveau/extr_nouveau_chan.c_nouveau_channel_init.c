#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {scalar_t__ family; scalar_t__ ram_user; } ;
struct nvif_device {TYPE_1__ info; } ;
struct nv_dma_v0 {scalar_t__ limit; scalar_t__ start; void* access; void* target; } ;
struct TYPE_13__ {scalar_t__ size; scalar_t__ base; scalar_t__ bridge; } ;
struct nouveau_drm {TYPE_2__ agp; } ;
struct TYPE_18__ {int handle; } ;
struct TYPE_17__ {int oclass; } ;
struct TYPE_16__ {int max; int ib_base; int ib_max; int ib_put; int ib_free; int put; int cur; int free; } ;
struct nouveau_channel {int user_put; int user_get; int user_get_hi; struct nouveau_drm* drm; TYPE_8__ nvsw; TYPE_6__ user; TYPE_5__ dma; TYPE_8__ gart; TYPE_4__* vmm; TYPE_8__ vram; int /*<<< orphan*/  kill; struct nvif_device* device; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_14__ {scalar_t__ limit; } ;
struct TYPE_15__ {TYPE_3__ vmm; } ;
struct TYPE_11__ {int (* context_new ) (struct nouveau_channel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int FERMI_CHANNEL_GPFIFO ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int NOUVEAU_DMA_SKIPS ; 
 int /*<<< orphan*/  NV906F_V0_NTFY_KILLED ; 
 int /*<<< orphan*/  NVIF_CLASS_SW_NV04 ; 
 scalar_t__ NV_DEVICE_INFO_V0_CELSIUS ; 
 scalar_t__ NV_DEVICE_INFO_V0_FERMI ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int /*<<< orphan*/  NV_DMA_IN_MEMORY ; 
 void* NV_DMA_V0_ACCESS_RDWR ; 
 void* NV_DMA_V0_ACCESS_VM ; 
 void* NV_DMA_V0_TARGET_AGP ; 
 void* NV_DMA_V0_TARGET_VM ; 
 void* NV_DMA_V0_TARGET_VRAM ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
 int /*<<< orphan*/  NvSubSw ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int /*<<< orphan*/  nouveau_channel_killed ; 
 TYPE_10__* nouveau_fence (struct nouveau_drm*) ; 
 int nvif_notify_get (int /*<<< orphan*/ *) ; 
 int nvif_notify_init (TYPE_6__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nvif_object_init (TYPE_6__*,int,int /*<<< orphan*/ ,struct nv_dma_v0*,int,TYPE_8__*) ; 
 int /*<<< orphan*/  nvif_object_map (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct nouveau_channel*) ; 

__attribute__((used)) static int
nouveau_channel_init(struct nouveau_channel *chan, u32 vram, u32 gart)
{
	struct nvif_device *device = chan->device;
	struct nouveau_drm *drm = chan->drm;
	struct nv_dma_v0 args = {};
	int ret, i;

	nvif_object_map(&chan->user, NULL, 0);

	if (chan->user.oclass >= FERMI_CHANNEL_GPFIFO) {
		ret = nvif_notify_init(&chan->user, nouveau_channel_killed,
				       true, NV906F_V0_NTFY_KILLED,
				       NULL, 0, 0, &chan->kill);
		if (ret == 0)
			ret = nvif_notify_get(&chan->kill);
		if (ret) {
			NV_ERROR(drm, "Failed to request channel kill "
				      "notification: %d\n", ret);
			return ret;
		}
	}

	/* allocate dma objects to cover all allowed vram, and gart */
	if (device->info.family < NV_DEVICE_INFO_V0_FERMI) {
		if (device->info.family >= NV_DEVICE_INFO_V0_TESLA) {
			args.target = NV_DMA_V0_TARGET_VM;
			args.access = NV_DMA_V0_ACCESS_VM;
			args.start = 0;
			args.limit = chan->vmm->vmm.limit - 1;
		} else {
			args.target = NV_DMA_V0_TARGET_VRAM;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = 0;
			args.limit = device->info.ram_user - 1;
		}

		ret = nvif_object_init(&chan->user, vram, NV_DMA_IN_MEMORY,
				       &args, sizeof(args), &chan->vram);
		if (ret)
			return ret;

		if (device->info.family >= NV_DEVICE_INFO_V0_TESLA) {
			args.target = NV_DMA_V0_TARGET_VM;
			args.access = NV_DMA_V0_ACCESS_VM;
			args.start = 0;
			args.limit = chan->vmm->vmm.limit - 1;
		} else
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

		ret = nvif_object_init(&chan->user, gart, NV_DMA_IN_MEMORY,
				       &args, sizeof(args), &chan->gart);
		if (ret)
			return ret;
	}

	/* initialise dma tracking parameters */
	switch (chan->user.oclass & 0x00ff) {
	case 0x006b:
	case 0x006e:
		chan->user_put = 0x40;
		chan->user_get = 0x44;
		chan->dma.max = (0x10000 / 4) - 2;
		break;
	default:
		chan->user_put = 0x40;
		chan->user_get = 0x44;
		chan->user_get_hi = 0x60;
		chan->dma.ib_base =  0x10000 / 4;
		chan->dma.ib_max  = (0x02000 / 8) - 1;
		chan->dma.ib_put  = 0;
		chan->dma.ib_free = chan->dma.ib_max - chan->dma.ib_put;
		chan->dma.max = chan->dma.ib_base;
		break;
	}

	chan->dma.put = 0;
	chan->dma.cur = chan->dma.put;
	chan->dma.free = chan->dma.max - chan->dma.cur;

	ret = RING_SPACE(chan, NOUVEAU_DMA_SKIPS);
	if (ret)
		return ret;

	for (i = 0; i < NOUVEAU_DMA_SKIPS; i++)
		OUT_RING(chan, 0x00000000);

	/* allocate software object class (used for fences on <= nv05) */
	if (device->info.family < NV_DEVICE_INFO_V0_CELSIUS) {
		ret = nvif_object_init(&chan->user, 0x006e,
				       NVIF_CLASS_SW_NV04,
				       NULL, 0, &chan->nvsw);
		if (ret)
			return ret;

		ret = RING_SPACE(chan, 2);
		if (ret)
			return ret;

		BEGIN_NV04(chan, NvSubSw, 0x0000, 1);
		OUT_RING  (chan, chan->nvsw.handle);
		FIRE_RING (chan);
	}

	/* initialise synchronisation */
	return nouveau_fence(chan->drm)->context_new(chan);
}