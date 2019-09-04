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
struct dma_fence {int dummy; } ;
struct amdgpu_fence {TYPE_1__* ring; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 struct amdgpu_fence* to_amdgpu_fence (struct dma_fence*) ; 

__attribute__((used)) static const char *amdgpu_fence_get_timeline_name(struct dma_fence *f)
{
	struct amdgpu_fence *fence = to_amdgpu_fence(f);
	return (const char *)fence->ring->name;
}