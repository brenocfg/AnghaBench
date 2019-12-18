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
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_ringbuffer {TYPE_1__* memptrs; } ;
struct adreno_gpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ADRENO_CP_RB_RPTR ; 
 int /*<<< orphan*/  adreno_gpu_read (struct adreno_gpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ adreno_is_a430 (struct adreno_gpu*) ; 

__attribute__((used)) static uint32_t get_rptr(struct adreno_gpu *adreno_gpu,
		struct msm_ringbuffer *ring)
{
	if (adreno_is_a430(adreno_gpu))
		return ring->memptrs->rptr = adreno_gpu_read(
			adreno_gpu, REG_ADRENO_CP_RB_RPTR);
	else
		return ring->memptrs->rptr;
}