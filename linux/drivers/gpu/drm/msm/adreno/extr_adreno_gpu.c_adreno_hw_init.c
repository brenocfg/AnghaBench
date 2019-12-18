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
struct msm_ringbuffer {int /*<<< orphan*/  iova; TYPE_1__* memptrs; int /*<<< orphan*/  seqno; int /*<<< orphan*/  start; int /*<<< orphan*/  next; int /*<<< orphan*/  cur; } ;
struct msm_gpu {int nr_rings; struct msm_ringbuffer** rb; int /*<<< orphan*/  name; } ;
struct adreno_gpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ rptr; int /*<<< orphan*/  fence; } ;

/* Variables and functions */
 int AXXX_CP_RB_CNTL_NO_UPDATE ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int MSM_GPU_RB_CNTL_DEFAULT ; 
 int /*<<< orphan*/  REG_ADRENO_CP_RB_BASE ; 
 int /*<<< orphan*/  REG_ADRENO_CP_RB_BASE_HI ; 
 int /*<<< orphan*/  REG_ADRENO_CP_RB_CNTL ; 
 int /*<<< orphan*/  REG_ADRENO_CP_RB_RPTR_ADDR ; 
 int /*<<< orphan*/  REG_ADRENO_CP_RB_RPTR_ADDR_HI ; 
 int /*<<< orphan*/  adreno_gpu_write (struct adreno_gpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adreno_gpu_write64 (struct adreno_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ adreno_is_a430 (struct adreno_gpu*) ; 
 int adreno_load_fw (struct adreno_gpu*) ; 
 int /*<<< orphan*/  rbmemptr (struct msm_ringbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rptr ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

int adreno_hw_init(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	int ret, i;

	DBG("%s", gpu->name);

	ret = adreno_load_fw(adreno_gpu);
	if (ret)
		return ret;

	for (i = 0; i < gpu->nr_rings; i++) {
		struct msm_ringbuffer *ring = gpu->rb[i];

		if (!ring)
			continue;

		ring->cur = ring->start;
		ring->next = ring->start;

		/* reset completed fence seqno: */
		ring->memptrs->fence = ring->seqno;
		ring->memptrs->rptr = 0;
	}

	/*
	 * Setup REG_CP_RB_CNTL.  The same value is used across targets (with
	 * the excpetion of A430 that disables the RPTR shadow) - the cacluation
	 * for the ringbuffer size and block size is moved to msm_gpu.h for the
	 * pre-processor to deal with and the A430 variant is ORed in here
	 */
	adreno_gpu_write(adreno_gpu, REG_ADRENO_CP_RB_CNTL,
		MSM_GPU_RB_CNTL_DEFAULT |
		(adreno_is_a430(adreno_gpu) ? AXXX_CP_RB_CNTL_NO_UPDATE : 0));

	/* Setup ringbuffer address - use ringbuffer[0] for GPU init */
	adreno_gpu_write64(adreno_gpu, REG_ADRENO_CP_RB_BASE,
		REG_ADRENO_CP_RB_BASE_HI, gpu->rb[0]->iova);

	if (!adreno_is_a430(adreno_gpu)) {
		adreno_gpu_write64(adreno_gpu, REG_ADRENO_CP_RB_RPTR_ADDR,
			REG_ADRENO_CP_RB_RPTR_ADDR_HI,
			rbmemptr(gpu->rb[0], rptr));
	}

	return 0;
}