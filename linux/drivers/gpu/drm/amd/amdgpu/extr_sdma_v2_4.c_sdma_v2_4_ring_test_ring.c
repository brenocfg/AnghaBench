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
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; scalar_t__ gpu_addr; } ;
struct amdgpu_device {unsigned int usec_timeout; TYPE_1__ wb; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SDMA_OP_WRITE ; 
 int SDMA_PKT_HEADER_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_HEADER_SUB_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_WRITE_UNTILED_DW_3_COUNT (int) ; 
 int /*<<< orphan*/  SDMA_SUBOP_WRITE_LINEAR ; 
 int /*<<< orphan*/  amdgpu_device_wb_free (struct amdgpu_device*,unsigned int) ; 
 int amdgpu_device_wb_get (struct amdgpu_device*,unsigned int*) ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int sdma_v2_4_ring_test_ring(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	unsigned i;
	unsigned index;
	int r;
	u32 tmp;
	u64 gpu_addr;

	r = amdgpu_device_wb_get(adev, &index);
	if (r)
		return r;

	gpu_addr = adev->wb.gpu_addr + (index * 4);
	tmp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_le32(tmp);

	r = amdgpu_ring_alloc(ring, 5);
	if (r)
		goto error_free_wb;

	amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_WRITE) |
			  SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_WRITE_LINEAR));
	amdgpu_ring_write(ring, lower_32_bits(gpu_addr));
	amdgpu_ring_write(ring, upper_32_bits(gpu_addr));
	amdgpu_ring_write(ring, SDMA_PKT_WRITE_UNTILED_DW_3_COUNT(1));
	amdgpu_ring_write(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);

	for (i = 0; i < adev->usec_timeout; i++) {
		tmp = le32_to_cpu(adev->wb.wb[index]);
		if (tmp == 0xDEADBEEF)
			break;
		udelay(1);
	}

	if (i >= adev->usec_timeout)
		r = -ETIMEDOUT;

error_free_wb:
	amdgpu_device_wb_free(adev, index);
	return r;
}