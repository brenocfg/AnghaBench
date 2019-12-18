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
struct TYPE_4__ {scalar_t__ seqno; } ;
struct etnaviv_fence {TYPE_2__ base; TYPE_1__* gpu; } ;
struct dma_fence {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_3__ {scalar_t__ completed_fence; } ;

/* Variables and functions */
 struct etnaviv_fence* to_etnaviv_fence (struct dma_fence*) ; 

__attribute__((used)) static bool etnaviv_fence_signaled(struct dma_fence *fence)
{
	struct etnaviv_fence *f = to_etnaviv_fence(fence);

	return (s32)(f->gpu->completed_fence - f->base.seqno) >= 0;
}