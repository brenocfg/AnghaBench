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
typedef  int /*<<< orphan*/  u64 ;
struct virtio_gpu_fence {TYPE_1__* drv; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_seq; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 struct virtio_gpu_fence* to_virtio_fence (struct dma_fence*) ; 

__attribute__((used)) static void virtio_timeline_value_str(struct dma_fence *f, char *str, int size)
{
	struct virtio_gpu_fence *fence = to_virtio_fence(f);

	snprintf(str, size, "%llu", (u64)atomic64_read(&fence->drv->last_seq));
}