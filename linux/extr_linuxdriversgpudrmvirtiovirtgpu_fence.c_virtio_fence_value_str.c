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
struct virtio_gpu_fence {int /*<<< orphan*/  seq; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 struct virtio_gpu_fence* to_virtio_fence (struct dma_fence*) ; 

__attribute__((used)) static void virtio_fence_value_str(struct dma_fence *f, char *str, int size)
{
	struct virtio_gpu_fence *fence = to_virtio_fence(f);

	snprintf(str, size, "%llu", fence->seq);
}