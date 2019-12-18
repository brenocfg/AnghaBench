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
typedef  scalar_t__ u16 ;
struct nvif_device {int /*<<< orphan*/  object; } ;
struct nv03_channel_dma_v0 {int /*<<< orphan*/  chid; int /*<<< orphan*/  offset; int /*<<< orphan*/  pushbuf; scalar_t__ version; } ;
struct nouveau_drm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  ctxdma; } ;
struct nouveau_channel {int /*<<< orphan*/  chid; int /*<<< orphan*/  user; TYPE_1__ push; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
#define  NV03_CHANNEL_DMA 131 
#define  NV10_CHANNEL_DMA 130 
#define  NV17_CHANNEL_DMA 129 
#define  NV40_CHANNEL_DMA 128 
 int /*<<< orphan*/  nouveau_channel_del (struct nouveau_channel**) ; 
 int nouveau_channel_prep (struct nouveau_drm*,struct nvif_device*,int,struct nouveau_channel**) ; 
 int /*<<< orphan*/  nvif_handle (int /*<<< orphan*/ *) ; 
 int nvif_object_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nv03_channel_dma_v0*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nouveau_channel_dma(struct nouveau_drm *drm, struct nvif_device *device,
		    struct nouveau_channel **pchan)
{
	static const u16 oclasses[] = { NV40_CHANNEL_DMA,
					NV17_CHANNEL_DMA,
					NV10_CHANNEL_DMA,
					NV03_CHANNEL_DMA,
					0 };
	const u16 *oclass = oclasses;
	struct nv03_channel_dma_v0 args;
	struct nouveau_channel *chan;
	int ret;

	/* allocate dma push buffer */
	ret = nouveau_channel_prep(drm, device, 0x10000, &chan);
	*pchan = chan;
	if (ret)
		return ret;

	/* create channel object */
	args.version = 0;
	args.pushbuf = nvif_handle(&chan->push.ctxdma);
	args.offset = chan->push.addr;

	do {
		ret = nvif_object_init(&device->object, 0, *oclass++,
				       &args, sizeof(args), &chan->user);
		if (ret == 0) {
			chan->chid = args.chid;
			return ret;
		}
	} while (ret && *oclass);

	nouveau_channel_del(pchan);
	return ret;
}