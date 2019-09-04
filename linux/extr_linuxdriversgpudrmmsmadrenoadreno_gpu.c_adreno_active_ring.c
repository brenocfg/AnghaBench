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
struct msm_ringbuffer {int dummy; } ;
struct msm_gpu {struct msm_ringbuffer** rb; } ;

/* Variables and functions */

struct msm_ringbuffer *adreno_active_ring(struct msm_gpu *gpu)
{
	return gpu->rb[0];
}