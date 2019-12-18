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
struct lima_fence {TYPE_2__* pipe; } ;
struct dma_fence {int dummy; } ;
struct TYPE_3__ {char const* name; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 struct lima_fence* to_lima_fence (struct dma_fence*) ; 

__attribute__((used)) static const char *lima_fence_get_timeline_name(struct dma_fence *fence)
{
	struct lima_fence *f = to_lima_fence(fence);

	return f->pipe->base.name;
}