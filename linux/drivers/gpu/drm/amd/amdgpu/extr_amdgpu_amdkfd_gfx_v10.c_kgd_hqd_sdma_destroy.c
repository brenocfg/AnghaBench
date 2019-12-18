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
typedef  int uint32_t ;
struct v10_sdma_mqd {int sdmax_rlcx_rb_rptr; int sdmax_rlcx_rb_rptr_hi; int /*<<< orphan*/  sdma_queue_id; int /*<<< orphan*/  sdma_engine_id; } ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 unsigned int HZ ; 
 int RREG32 (int) ; 
 int SDMA0_RLC0_CONTEXT_STATUS__IDLE_MASK ; 
 int SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int get_sdma_base_addr (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v10_sdma_mqd* get_sdma_mqd (void*) ; 
 unsigned int jiffies ; 
 int mmSDMA0_RLC0_CONTEXT_STATUS ; 
 int mmSDMA0_RLC0_DOORBELL ; 
 int mmSDMA0_RLC0_RB_CNTL ; 
 int mmSDMA0_RLC0_RB_RPTR ; 
 int mmSDMA0_RLC0_RB_RPTR_HI ; 
 scalar_t__ time_after (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int kgd_hqd_sdma_destroy(struct kgd_dev *kgd, void *mqd,
				unsigned int utimeout)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	struct v10_sdma_mqd *m;
	uint32_t sdma_base_addr;
	uint32_t temp;
	unsigned long end_jiffies = (utimeout * HZ / 1000) + jiffies;

	m = get_sdma_mqd(mqd);
	sdma_base_addr = get_sdma_base_addr(adev, m->sdma_engine_id,
					    m->sdma_queue_id);

	temp = RREG32(sdma_base_addr + mmSDMA0_RLC0_RB_CNTL);
	temp = temp & ~SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK;
	WREG32(sdma_base_addr + mmSDMA0_RLC0_RB_CNTL, temp);

	while (true) {
		temp = RREG32(sdma_base_addr + mmSDMA0_RLC0_CONTEXT_STATUS);
		if (temp & SDMA0_RLC0_CONTEXT_STATUS__IDLE_MASK)
			break;
		if (time_after(jiffies, end_jiffies))
			return -ETIME;
		usleep_range(500, 1000);
	}

	WREG32(sdma_base_addr + mmSDMA0_RLC0_DOORBELL, 0);
	WREG32(sdma_base_addr + mmSDMA0_RLC0_RB_CNTL,
		RREG32(sdma_base_addr + mmSDMA0_RLC0_RB_CNTL) |
		SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK);

	m->sdmax_rlcx_rb_rptr = RREG32(sdma_base_addr + mmSDMA0_RLC0_RB_RPTR);
	m->sdmax_rlcx_rb_rptr_hi =
		RREG32(sdma_base_addr + mmSDMA0_RLC0_RB_RPTR_HI);

	return 0;
}