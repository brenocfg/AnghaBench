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
struct TYPE_2__ {int /*<<< orphan*/  sync32; int /*<<< orphan*/  emit32; } ;
struct nv84_fence_chan {TYPE_1__ base; } ;
struct nouveau_channel {struct nv84_fence_chan* fence; } ;

/* Variables and functions */
 int nv84_fence_context_new (struct nouveau_channel*) ; 
 int /*<<< orphan*/  nvc0_fence_emit32 ; 
 int /*<<< orphan*/  nvc0_fence_sync32 ; 

__attribute__((used)) static int
nvc0_fence_context_new(struct nouveau_channel *chan)
{
	int ret = nv84_fence_context_new(chan);
	if (ret == 0) {
		struct nv84_fence_chan *fctx = chan->fence;
		fctx->base.emit32 = nvc0_fence_emit32;
		fctx->base.sync32 = nvc0_fence_sync32;
	}
	return ret;
}