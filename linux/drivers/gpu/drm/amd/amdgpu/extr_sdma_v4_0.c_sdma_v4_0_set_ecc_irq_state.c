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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
 int AMDGPU_IRQ_STATE_ENABLE ; 
 int /*<<< orphan*/  ECC_INT_ENABLE ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SDMA (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA0_EDC_CONFIG ; 
 int /*<<< orphan*/  WREG32_SDMA (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSDMA0_EDC_CONFIG ; 

__attribute__((used)) static int sdma_v4_0_set_ecc_irq_state(struct amdgpu_device *adev,
					struct amdgpu_irq_src *source,
					unsigned type,
					enum amdgpu_interrupt_state state)
{
	u32 sdma_edc_config;

	sdma_edc_config = RREG32_SDMA(type, mmSDMA0_EDC_CONFIG);
	sdma_edc_config = REG_SET_FIELD(sdma_edc_config, SDMA0_EDC_CONFIG, ECC_INT_ENABLE,
		       state == AMDGPU_IRQ_STATE_ENABLE ? 1 : 0);
	WREG32_SDMA(type, mmSDMA0_EDC_CONFIG, sdma_edc_config);

	return 0;
}