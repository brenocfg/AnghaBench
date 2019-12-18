#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nouveau_fence {int dummy; } ;
struct nouveau_cli {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {scalar_t__ client; } ;
struct nouveau_channel {int /*<<< orphan*/  chid; TYPE_1__ user; int /*<<< orphan*/  killed; scalar_t__ fence; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_PRINTK (int /*<<< orphan*/ ,struct nouveau_cli*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err ; 
 scalar_t__ likely (int) ; 
 int nouveau_fence_new (struct nouveau_channel*,int,struct nouveau_fence**) ; 
 int /*<<< orphan*/  nouveau_fence_unref (struct nouveau_fence**) ; 
 int nouveau_fence_wait (struct nouveau_fence*,int,int) ; 
 TYPE_2__* nvxx_client (int /*<<< orphan*/ *) ; 

int
nouveau_channel_idle(struct nouveau_channel *chan)
{
	if (likely(chan && chan->fence && !atomic_read(&chan->killed))) {
		struct nouveau_cli *cli = (void *)chan->user.client;
		struct nouveau_fence *fence = NULL;
		int ret;

		ret = nouveau_fence_new(chan, false, &fence);
		if (!ret) {
			ret = nouveau_fence_wait(fence, false, false);
			nouveau_fence_unref(&fence);
		}

		if (ret) {
			NV_PRINTK(err, cli, "failed to idle channel %d [%s]\n",
				  chan->chid, nvxx_client(&cli->base)->name);
			return ret;
		}
	}
	return 0;
}