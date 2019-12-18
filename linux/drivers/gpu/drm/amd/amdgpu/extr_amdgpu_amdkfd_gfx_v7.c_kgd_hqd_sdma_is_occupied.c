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
struct kgd_dev {int dummy; } ;
struct cik_sdma_rlc_registers {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int RREG32 (int) ; 
 int SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int get_sdma_base_addr (struct cik_sdma_rlc_registers*) ; 
 struct cik_sdma_rlc_registers* get_sdma_mqd (void*) ; 
 int mmSDMA0_RLC0_RB_CNTL ; 

__attribute__((used)) static bool kgd_hqd_sdma_is_occupied(struct kgd_dev *kgd, void *mqd)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	struct cik_sdma_rlc_registers *m;
	uint32_t sdma_base_addr;
	uint32_t sdma_rlc_rb_cntl;

	m = get_sdma_mqd(mqd);
	sdma_base_addr = get_sdma_base_addr(m);

	sdma_rlc_rb_cntl = RREG32(sdma_base_addr + mmSDMA0_RLC0_RB_CNTL);

	if (sdma_rlc_rb_cntl & SDMA0_RLC0_RB_CNTL__RB_ENABLE_MASK)
		return true;

	return false;
}