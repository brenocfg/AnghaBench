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
struct etnaviv_fence {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 TYPE_1__ base ; 
 int /*<<< orphan*/  kfree_rcu (struct etnaviv_fence*,int /*<<< orphan*/ ) ; 
 struct etnaviv_fence* to_etnaviv_fence (struct dma_fence*) ; 

__attribute__((used)) static void etnaviv_fence_release(struct dma_fence *fence)
{
	struct etnaviv_fence *f = to_etnaviv_fence(fence);

	kfree_rcu(f, base.rcu);
}