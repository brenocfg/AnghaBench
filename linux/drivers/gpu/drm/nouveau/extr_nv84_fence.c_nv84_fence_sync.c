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
typedef  scalar_t__ u64 ;
struct TYPE_5__ {int (* sync32 ) (struct nouveau_channel*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct nv84_fence_chan {TYPE_2__ base; TYPE_1__* vma; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqno; } ;
struct nouveau_fence {TYPE_3__ base; } ;
struct nouveau_channel {int chid; struct nv84_fence_chan* fence; } ;
struct TYPE_4__ {scalar_t__ addr; } ;

/* Variables and functions */
 int stub1 (struct nouveau_channel*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv84_fence_sync(struct nouveau_fence *fence,
		struct nouveau_channel *prev, struct nouveau_channel *chan)
{
	struct nv84_fence_chan *fctx = chan->fence;
	u64 addr = fctx->vma->addr + prev->chid * 16;

	return fctx->base.sync32(chan, addr, fence->base.seqno);
}