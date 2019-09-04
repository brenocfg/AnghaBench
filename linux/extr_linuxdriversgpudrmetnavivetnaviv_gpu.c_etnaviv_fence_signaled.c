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
struct TYPE_2__ {int /*<<< orphan*/  seqno; } ;
struct etnaviv_fence {TYPE_1__ base; int /*<<< orphan*/  gpu; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int fence_completed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct etnaviv_fence* to_etnaviv_fence (struct dma_fence*) ; 

__attribute__((used)) static bool etnaviv_fence_signaled(struct dma_fence *fence)
{
	struct etnaviv_fence *f = to_etnaviv_fence(fence);

	return fence_completed(f->gpu, f->base.seqno);
}