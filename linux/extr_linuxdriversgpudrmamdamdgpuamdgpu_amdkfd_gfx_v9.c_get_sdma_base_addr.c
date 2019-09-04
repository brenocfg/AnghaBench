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
typedef  unsigned int uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA0 ; 
 int /*<<< orphan*/  SDMA1 ; 
 unsigned int SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int mmSDMA0_RLC0_RB_CNTL ; 
 unsigned int mmSDMA0_RLC1_RB_CNTL ; 
 unsigned int mmSDMA1_RLC0_RB_CNTL ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 

__attribute__((used)) static uint32_t get_sdma_base_addr(struct amdgpu_device *adev,
				unsigned int engine_id,
				unsigned int queue_id)
{
	uint32_t base[2] = {
		SOC15_REG_OFFSET(SDMA0, 0,
				 mmSDMA0_RLC0_RB_CNTL) - mmSDMA0_RLC0_RB_CNTL,
		SOC15_REG_OFFSET(SDMA1, 0,
				 mmSDMA1_RLC0_RB_CNTL) - mmSDMA1_RLC0_RB_CNTL
	};
	uint32_t retval;

	retval = base[engine_id] + queue_id * (mmSDMA0_RLC1_RB_CNTL -
					       mmSDMA0_RLC0_RB_CNTL);

	pr_debug("sdma base address: 0x%x\n", retval);

	return retval;
}