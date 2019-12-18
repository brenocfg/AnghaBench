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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_ib {int* ptr; int length_dw; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; scalar_t__ gpu_addr; } ;
struct amdgpu_device {TYPE_1__ wb; } ;
typedef  int /*<<< orphan*/  ib ;

/* Variables and functions */
 long EINVAL ; 
 long ETIMEDOUT ; 
 int /*<<< orphan*/  SDMA_OP_NOP ; 
 int /*<<< orphan*/  SDMA_OP_WRITE ; 
 int SDMA_PKT_HEADER_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_HEADER_SUB_OP (int /*<<< orphan*/ ) ; 
 void* SDMA_PKT_NOP_HEADER_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_WRITE_UNTILED_DW_3_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA_SUBOP_WRITE_LINEAR ; 
 int /*<<< orphan*/  amdgpu_device_wb_free (struct amdgpu_device*,unsigned int) ; 
 long amdgpu_device_wb_get (struct amdgpu_device*,unsigned int*) ; 
 int /*<<< orphan*/  amdgpu_ib_free (struct amdgpu_device*,struct amdgpu_ib*,int /*<<< orphan*/ *) ; 
 long amdgpu_ib_get (struct amdgpu_device*,int /*<<< orphan*/ *,int,struct amdgpu_ib*) ; 
 long amdgpu_ib_schedule (struct amdgpu_ring*,int,struct amdgpu_ib*,int /*<<< orphan*/ *,struct dma_fence**) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,long) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct amdgpu_ib*,int /*<<< orphan*/ ,int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int sdma_v4_0_ring_test_ib(struct amdgpu_ring *ring, long timeout)
{
	struct amdgpu_device *adev = ring->adev;
	struct amdgpu_ib ib;
	struct dma_fence *f = NULL;
	unsigned index;
	long r;
	u32 tmp = 0;
	u64 gpu_addr;

	r = amdgpu_device_wb_get(adev, &index);
	if (r)
		return r;

	gpu_addr = adev->wb.gpu_addr + (index * 4);
	tmp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_le32(tmp);
	memset(&ib, 0, sizeof(ib));
	r = amdgpu_ib_get(adev, NULL, 256, &ib);
	if (r)
		goto err0;

	ib.ptr[0] = SDMA_PKT_HEADER_OP(SDMA_OP_WRITE) |
		SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_WRITE_LINEAR);
	ib.ptr[1] = lower_32_bits(gpu_addr);
	ib.ptr[2] = upper_32_bits(gpu_addr);
	ib.ptr[3] = SDMA_PKT_WRITE_UNTILED_DW_3_COUNT(0);
	ib.ptr[4] = 0xDEADBEEF;
	ib.ptr[5] = SDMA_PKT_NOP_HEADER_OP(SDMA_OP_NOP);
	ib.ptr[6] = SDMA_PKT_NOP_HEADER_OP(SDMA_OP_NOP);
	ib.ptr[7] = SDMA_PKT_NOP_HEADER_OP(SDMA_OP_NOP);
	ib.length_dw = 8;

	r = amdgpu_ib_schedule(ring, 1, &ib, NULL, &f);
	if (r)
		goto err1;

	r = dma_fence_wait_timeout(f, false, timeout);
	if (r == 0) {
		r = -ETIMEDOUT;
		goto err1;
	} else if (r < 0) {
		goto err1;
	}
	tmp = le32_to_cpu(adev->wb.wb[index]);
	if (tmp == 0xDEADBEEF)
		r = 0;
	else
		r = -EINVAL;

err1:
	amdgpu_ib_free(adev, &ib, NULL);
	dma_fence_put(f);
err0:
	amdgpu_device_wb_free(adev, index);
	return r;
}