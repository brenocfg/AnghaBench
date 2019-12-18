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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ client; } ;
struct nvif_device {TYPE_1__ object; } ;
struct nouveau_drm {int dummy; } ;
struct TYPE_6__ {int super; } ;
struct nouveau_cli {TYPE_3__ base; } ;
struct nouveau_channel {int /*<<< orphan*/  inst; TYPE_2__* vmm; } ;
struct TYPE_5__ {int /*<<< orphan*/  svmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_PRINTK (int /*<<< orphan*/ ,struct nouveau_cli*,char*,int) ; 
 int /*<<< orphan*/  dbg ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  nouveau_channel_del (struct nouveau_channel**) ; 
 int nouveau_channel_dma (struct nouveau_drm*,struct nvif_device*,struct nouveau_channel**) ; 
 int nouveau_channel_ind (struct nouveau_drm*,struct nvif_device*,int /*<<< orphan*/ ,int,struct nouveau_channel**) ; 
 int nouveau_channel_init (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nouveau_svmm_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nouveau_channel_new(struct nouveau_drm *drm, struct nvif_device *device,
		    u32 arg0, u32 arg1, bool priv,
		    struct nouveau_channel **pchan)
{
	struct nouveau_cli *cli = (void *)device->object.client;
	bool super;
	int ret;

	/* hack until fencenv50 is fixed, and agp access relaxed */
	super = cli->base.super;
	cli->base.super = true;

	ret = nouveau_channel_ind(drm, device, arg0, priv, pchan);
	if (ret) {
		NV_PRINTK(dbg, cli, "ib channel create, %d\n", ret);
		ret = nouveau_channel_dma(drm, device, pchan);
		if (ret) {
			NV_PRINTK(dbg, cli, "dma channel create, %d\n", ret);
			goto done;
		}
	}

	ret = nouveau_channel_init(*pchan, arg0, arg1);
	if (ret) {
		NV_PRINTK(err, cli, "channel failed to initialise, %d\n", ret);
		nouveau_channel_del(pchan);
	}

	ret = nouveau_svmm_join((*pchan)->vmm->svmm, (*pchan)->inst);
	if (ret)
		nouveau_channel_del(pchan);

done:
	cli->base.super = super;
	return ret;
}