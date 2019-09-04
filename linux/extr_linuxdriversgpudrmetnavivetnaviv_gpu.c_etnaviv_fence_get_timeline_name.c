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
struct etnaviv_fence {TYPE_1__* gpu; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char const* dev_name (int /*<<< orphan*/ ) ; 
 struct etnaviv_fence* to_etnaviv_fence (struct dma_fence*) ; 

__attribute__((used)) static const char *etnaviv_fence_get_timeline_name(struct dma_fence *fence)
{
	struct etnaviv_fence *f = to_etnaviv_fence(fence);

	return dev_name(f->gpu->dev);
}