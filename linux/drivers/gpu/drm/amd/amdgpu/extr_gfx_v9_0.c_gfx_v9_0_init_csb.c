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
struct TYPE_3__ {int clear_state_gpu_addr; int clear_state_size; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_RLC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmRLC_CSIB_ADDR_HI ; 
 int /*<<< orphan*/  mmRLC_CSIB_ADDR_LO ; 
 int /*<<< orphan*/  mmRLC_CSIB_LENGTH ; 

__attribute__((used)) static void gfx_v9_0_init_csb(struct amdgpu_device *adev)
{
	/* csib */
	WREG32_RLC(SOC15_REG_OFFSET(GC, 0, mmRLC_CSIB_ADDR_HI),
			adev->gfx.rlc.clear_state_gpu_addr >> 32);
	WREG32_RLC(SOC15_REG_OFFSET(GC, 0, mmRLC_CSIB_ADDR_LO),
			adev->gfx.rlc.clear_state_gpu_addr & 0xfffffffc);
	WREG32_RLC(SOC15_REG_OFFSET(GC, 0, mmRLC_CSIB_LENGTH),
			adev->gfx.rlc.clear_state_size);
}