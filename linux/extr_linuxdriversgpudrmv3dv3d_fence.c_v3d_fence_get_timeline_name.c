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
struct v3d_fence {scalar_t__ queue; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 scalar_t__ V3D_BIN ; 
 struct v3d_fence* to_v3d_fence (struct dma_fence*) ; 

__attribute__((used)) static const char *v3d_fence_get_timeline_name(struct dma_fence *fence)
{
	struct v3d_fence *f = to_v3d_fence(fence);

	if (f->queue == V3D_BIN)
		return "v3d-bin";
	else
		return "v3d-render";
}