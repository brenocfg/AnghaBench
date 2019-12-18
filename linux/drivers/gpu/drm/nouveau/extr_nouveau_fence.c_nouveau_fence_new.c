#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nouveau_fence {int dummy; } ;
struct nouveau_channel {int /*<<< orphan*/  fence; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nouveau_fence* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nouveau_fence_emit (struct nouveau_fence*,struct nouveau_channel*) ; 
 int /*<<< orphan*/  nouveau_fence_unref (struct nouveau_fence**) ; 
 scalar_t__ unlikely (int) ; 

int
nouveau_fence_new(struct nouveau_channel *chan, bool sysmem,
		  struct nouveau_fence **pfence)
{
	struct nouveau_fence *fence;
	int ret = 0;

	if (unlikely(!chan->fence))
		return -ENODEV;

	fence = kzalloc(sizeof(*fence), GFP_KERNEL);
	if (!fence)
		return -ENOMEM;

	ret = nouveau_fence_emit(fence, chan);
	if (ret)
		nouveau_fence_unref(&fence);

	*pfence = fence;
	return ret;
}