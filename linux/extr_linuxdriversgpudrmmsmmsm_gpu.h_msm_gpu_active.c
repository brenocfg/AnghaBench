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
struct msm_ringbuffer {scalar_t__ seqno; TYPE_1__* memptrs; } ;
struct msm_gpu {int nr_rings; struct msm_ringbuffer** rb; } ;
struct TYPE_2__ {scalar_t__ fence; } ;

/* Variables and functions */

__attribute__((used)) static inline bool msm_gpu_active(struct msm_gpu *gpu)
{
	int i;

	for (i = 0; i < gpu->nr_rings; i++) {
		struct msm_ringbuffer *ring = gpu->rb[i];

		if (ring->seqno > ring->memptrs->fence)
			return true;
	}

	return false;
}