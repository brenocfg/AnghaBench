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
struct nouveau_fence_chan {scalar_t__ (* read ) (struct nouveau_channel*) ;} ;
struct TYPE_2__ {scalar_t__ seqno; } ;
struct nouveau_fence {TYPE_1__ base; int /*<<< orphan*/  channel; } ;
struct nouveau_channel {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct nouveau_fence* from_fence (struct dma_fence*) ; 
 struct nouveau_fence_chan* nouveau_fctx (struct nouveau_fence*) ; 
 struct nouveau_channel* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ stub1 (struct nouveau_channel*) ; 

__attribute__((used)) static bool nouveau_fence_is_signaled(struct dma_fence *f)
{
	struct nouveau_fence *fence = from_fence(f);
	struct nouveau_fence_chan *fctx = nouveau_fctx(fence);
	struct nouveau_channel *chan;
	bool ret = false;

	rcu_read_lock();
	chan = rcu_dereference(fence->channel);
	if (chan)
		ret = (int)(fctx->read(chan) - fence->base.seqno) >= 0;
	rcu_read_unlock();

	return ret;
}