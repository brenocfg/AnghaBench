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
struct panfrost_fence {int queue; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct panfrost_fence* to_panfrost_fence (struct dma_fence*) ; 

__attribute__((used)) static const char *panfrost_fence_get_timeline_name(struct dma_fence *fence)
{
	struct panfrost_fence *f = to_panfrost_fence(fence);

	switch (f->queue) {
	case 0:
		return "panfrost-js-0";
	case 1:
		return "panfrost-js-1";
	case 2:
		return "panfrost-js-2";
	default:
		return NULL;
	}
}