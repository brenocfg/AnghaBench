#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int super; } ;
struct nouveau_cli {TYPE_3__ base; } ;
struct TYPE_12__ {scalar_t__ client; } ;
struct TYPE_10__ {TYPE_6__* buffer; int /*<<< orphan*/  vma; TYPE_4__ ctxdma; } ;
struct nouveau_channel {TYPE_2__ push; TYPE_4__ user; int /*<<< orphan*/  kill; TYPE_4__ vram; TYPE_4__ gart; TYPE_4__ nvsw; int /*<<< orphan*/  inst; TYPE_1__* vmm; int /*<<< orphan*/  drm; scalar_t__ fence; } ;
struct TYPE_14__ {scalar_t__ pin_refcnt; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* context_del ) (struct nouveau_channel*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  svmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nouveau_channel*) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,TYPE_6__**) ; 
 int /*<<< orphan*/  nouveau_bo_unmap (TYPE_6__*) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (TYPE_6__*) ; 
 TYPE_5__* nouveau_fence (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_svmm_part (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_vma_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_notify_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_object_fini (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_channel*) ; 

void
nouveau_channel_del(struct nouveau_channel **pchan)
{
	struct nouveau_channel *chan = *pchan;
	if (chan) {
		struct nouveau_cli *cli = (void *)chan->user.client;
		bool super;

		if (cli) {
			super = cli->base.super;
			cli->base.super = true;
		}

		if (chan->fence)
			nouveau_fence(chan->drm)->context_del(chan);

		if (cli)
			nouveau_svmm_part(chan->vmm->svmm, chan->inst);

		nvif_object_fini(&chan->nvsw);
		nvif_object_fini(&chan->gart);
		nvif_object_fini(&chan->vram);
		nvif_notify_fini(&chan->kill);
		nvif_object_fini(&chan->user);
		nvif_object_fini(&chan->push.ctxdma);
		nouveau_vma_del(&chan->push.vma);
		nouveau_bo_unmap(chan->push.buffer);
		if (chan->push.buffer && chan->push.buffer->pin_refcnt)
			nouveau_bo_unpin(chan->push.buffer);
		nouveau_bo_ref(NULL, &chan->push.buffer);
		kfree(chan);

		if (cli)
			cli->base.super = super;
	}
	*pchan = NULL;
}