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
struct TYPE_2__ {scalar_t__ reg_offset; } ;
struct amdgpu_device {TYPE_1__ rmmio_remap; } ;

/* Variables and functions */
 scalar_t__ KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL ; 
 scalar_t__ KFD_MMIO_REMAP_HDP_REG_FLUSH_CNTL ; 
 int /*<<< orphan*/  NBIO ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmREMAP_HDP_MEM_FLUSH_CNTL ; 
 int /*<<< orphan*/  mmREMAP_HDP_REG_FLUSH_CNTL ; 

__attribute__((used)) static void nbio_v7_4_remap_hdp_registers(struct amdgpu_device *adev)
{
	WREG32_SOC15(NBIO, 0, mmREMAP_HDP_MEM_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL);
	WREG32_SOC15(NBIO, 0, mmREMAP_HDP_REG_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_REG_FLUSH_CNTL);
}