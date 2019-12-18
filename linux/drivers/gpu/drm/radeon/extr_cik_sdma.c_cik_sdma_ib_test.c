#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct radeon_ring {scalar_t__ idx; } ;
struct radeon_ib {int* ptr; int length_dw; TYPE_2__* fence; } ;
struct TYPE_3__ {int /*<<< orphan*/ * wb; scalar_t__ gpu_addr; } ;
struct radeon_device {unsigned int usec_timeout; TYPE_1__ wb; } ;
struct TYPE_4__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 unsigned int CAYMAN_WB_DMA1_RING_TEST_OFFSET ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ R600_RING_TYPE_DMA_INDEX ; 
 unsigned int R600_WB_DMA_RING_TEST_OFFSET ; 
 int /*<<< orphan*/  RADEON_USEC_IB_TEST_TIMEOUT ; 
 int /*<<< orphan*/  SDMA_OPCODE_WRITE ; 
 int SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA_WRITE_SUB_OPCODE_LINEAR ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int lower_32_bits (scalar_t__) ; 
 int radeon_fence_wait_timeout (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ib_free (struct radeon_device*,struct radeon_ib*) ; 
 int radeon_ib_get (struct radeon_device*,scalar_t__,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int radeon_ib_schedule (struct radeon_device*,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int upper_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 

int cik_sdma_ib_test(struct radeon_device *rdev, struct radeon_ring *ring)
{
	struct radeon_ib ib;
	unsigned i;
	unsigned index;
	int r;
	u32 tmp = 0;
	u64 gpu_addr;

	if (ring->idx == R600_RING_TYPE_DMA_INDEX)
		index = R600_WB_DMA_RING_TEST_OFFSET;
	else
		index = CAYMAN_WB_DMA1_RING_TEST_OFFSET;

	gpu_addr = rdev->wb.gpu_addr + index;

	tmp = 0xCAFEDEAD;
	rdev->wb.wb[index/4] = cpu_to_le32(tmp);

	r = radeon_ib_get(rdev, ring->idx, &ib, NULL, 256);
	if (r) {
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		return r;
	}

	ib.ptr[0] = SDMA_PACKET(SDMA_OPCODE_WRITE, SDMA_WRITE_SUB_OPCODE_LINEAR, 0);
	ib.ptr[1] = lower_32_bits(gpu_addr);
	ib.ptr[2] = upper_32_bits(gpu_addr);
	ib.ptr[3] = 1;
	ib.ptr[4] = 0xDEADBEEF;
	ib.length_dw = 5;

	r = radeon_ib_schedule(rdev, &ib, NULL, false);
	if (r) {
		radeon_ib_free(rdev, &ib);
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
		return r;
	}
	r = radeon_fence_wait_timeout(ib.fence, false, usecs_to_jiffies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	if (r < 0) {
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		return r;
	} else if (r == 0) {
		DRM_ERROR("radeon: fence wait timed out.\n");
		return -ETIMEDOUT;
	}
	r = 0;
	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = le32_to_cpu(rdev->wb.wb[index/4]);
		if (tmp == 0xDEADBEEF)
			break;
		udelay(1);
	}
	if (i < rdev->usec_timeout) {
		DRM_INFO("ib test on ring %d succeeded in %u usecs\n", ib.fence->ring, i);
	} else {
		DRM_ERROR("radeon: ib test failed (0x%08X)\n", tmp);
		r = -EINVAL;
	}
	radeon_ib_free(rdev, &ib);
	return r;
}