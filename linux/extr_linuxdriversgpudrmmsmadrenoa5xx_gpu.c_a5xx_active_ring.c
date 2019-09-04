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
struct msm_gpu {int dummy; } ;
struct adreno_gpu {int dummy; } ;
struct a5xx_gpu {struct msm_ringbuffer* cur_ring; } ;

/* Variables and functions */
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static struct msm_ringbuffer *a5xx_active_ring(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);

	return a5xx_gpu->cur_ring;
}