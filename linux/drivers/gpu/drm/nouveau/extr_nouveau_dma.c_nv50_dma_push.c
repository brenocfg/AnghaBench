#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct nvif_user {TYPE_5__* func; } ;
struct TYPE_12__ {int ib_put; int ib_base; int ib_free; int ib_max; } ;
struct TYPE_10__ {struct nouveau_bo* buffer; } ;
struct nouveau_channel {TYPE_6__ dma; int /*<<< orphan*/  token; int /*<<< orphan*/  user; TYPE_4__ push; TYPE_3__* drm; } ;
struct nouveau_bo {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* doorbell ) (struct nvif_user*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {struct nvif_user user; } ;
struct TYPE_8__ {TYPE_1__ device; } ;
struct TYPE_9__ {TYPE_2__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  nouveau_bo_rd32 (struct nouveau_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_wr32 (struct nouveau_bo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvif_wr32 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nvif_user*,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

void
nv50_dma_push(struct nouveau_channel *chan, u64 offset, int length)
{
	struct nvif_user *user = &chan->drm->client.device.user;
	struct nouveau_bo *pb = chan->push.buffer;
	int ip = (chan->dma.ib_put * 2) + chan->dma.ib_base;

	BUG_ON(chan->dma.ib_free < 1);

	nouveau_bo_wr32(pb, ip++, lower_32_bits(offset));
	nouveau_bo_wr32(pb, ip++, upper_32_bits(offset) | length << 8);

	chan->dma.ib_put = (chan->dma.ib_put + 1) & chan->dma.ib_max;

	mb();
	/* Flush writes. */
	nouveau_bo_rd32(pb, 0);

	nvif_wr32(&chan->user, 0x8c, chan->dma.ib_put);
	if (user->func && user->func->doorbell)
		user->func->doorbell(user, chan->token);
	chan->dma.ib_free--;
}