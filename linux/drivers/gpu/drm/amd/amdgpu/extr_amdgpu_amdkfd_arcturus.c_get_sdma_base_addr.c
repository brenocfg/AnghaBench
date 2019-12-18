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
 int /*<<< orphan*/  SDMA2 ; 
 int /*<<< orphan*/  SDMA3 ; 
 int /*<<< orphan*/  SDMA4 ; 
 int /*<<< orphan*/  SDMA5 ; 
 int /*<<< orphan*/  SDMA6 ; 
 int /*<<< orphan*/  SDMA7 ; 
 unsigned int SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int mmSDMA0_RLC0_RB_CNTL ; 
 unsigned int mmSDMA0_RLC1_RB_CNTL ; 
 unsigned int mmSDMA1_RLC0_RB_CNTL ; 
 unsigned int mmSDMA2_RLC0_RB_CNTL ; 
 unsigned int mmSDMA3_RLC0_RB_CNTL ; 
 unsigned int mmSDMA4_RLC0_RB_CNTL ; 
 unsigned int mmSDMA5_RLC0_RB_CNTL ; 
 unsigned int mmSDMA6_RLC0_RB_CNTL ; 
 unsigned int mmSDMA7_RLC0_RB_CNTL ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 

__attribute__((used)) static uint32_t get_sdma_base_addr(struct amdgpu_device *adev,
				unsigned int engine_id,
				unsigned int queue_id)
{
	uint32_t base[8] = {
		SOC15_REG_OFFSET(SDMA0, 0,
				 mmSDMA0_RLC0_RB_CNTL) - mmSDMA0_RLC0_RB_CNTL,
		SOC15_REG_OFFSET(SDMA1, 0,
				 mmSDMA1_RLC0_RB_CNTL) - mmSDMA1_RLC0_RB_CNTL,
		SOC15_REG_OFFSET(SDMA2, 0,
				 mmSDMA2_RLC0_RB_CNTL) - mmSDMA2_RLC0_RB_CNTL,
		SOC15_REG_OFFSET(SDMA3, 0,
				 mmSDMA3_RLC0_RB_CNTL) - mmSDMA3_RLC0_RB_CNTL,
		SOC15_REG_OFFSET(SDMA4, 0,
				 mmSDMA4_RLC0_RB_CNTL) - mmSDMA4_RLC0_RB_CNTL,
		SOC15_REG_OFFSET(SDMA5, 0,
				 mmSDMA5_RLC0_RB_CNTL) - mmSDMA5_RLC0_RB_CNTL,
		SOC15_REG_OFFSET(SDMA6, 0,
				 mmSDMA6_RLC0_RB_CNTL) - mmSDMA6_RLC0_RB_CNTL,
		SOC15_REG_OFFSET(SDMA7, 0,
				 mmSDMA7_RLC0_RB_CNTL) - mmSDMA7_RLC0_RB_CNTL
	};
	uint32_t retval;

	retval = base[engine_id] + queue_id * (mmSDMA0_RLC1_RB_CNTL -
					       mmSDMA0_RLC0_RB_CNTL);

	pr_debug("sdma base address: 0x%x\n", retval);

	return retval;
}