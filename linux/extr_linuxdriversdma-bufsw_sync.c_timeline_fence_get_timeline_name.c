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
struct sync_timeline {char const* name; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct sync_timeline* dma_fence_parent (struct dma_fence*) ; 

__attribute__((used)) static const char *timeline_fence_get_timeline_name(struct dma_fence *fence)
{
	struct sync_timeline *parent = dma_fence_parent(fence);

	return parent->name;
}