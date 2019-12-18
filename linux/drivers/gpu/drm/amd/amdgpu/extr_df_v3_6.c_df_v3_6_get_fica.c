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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct amdgpu_device {int /*<<< orphan*/  pcie_idx_lock; TYPE_1__* nbio_funcs; } ;
struct TYPE_2__ {unsigned long (* get_pcie_index_offset ) (struct amdgpu_device*) ;unsigned long (* get_pcie_data_offset ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int RREG32 (unsigned long) ; 
 int /*<<< orphan*/  WREG32 (unsigned long,int) ; 
 int smnDF_PIE_AON_FabricIndirectConfigAccessAddress3 ; 
 int smnDF_PIE_AON_FabricIndirectConfigAccessDataHi3 ; 
 int smnDF_PIE_AON_FabricIndirectConfigAccessDataLo3 ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long stub1 (struct amdgpu_device*) ; 
 unsigned long stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static uint64_t df_v3_6_get_fica(struct amdgpu_device *adev,
				 uint32_t ficaa_val)
{
	unsigned long flags, address, data;
	uint32_t ficadl_val, ficadh_val;

	address = adev->nbio_funcs->get_pcie_index_offset(adev);
	data = adev->nbio_funcs->get_pcie_data_offset(adev);

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(address, smnDF_PIE_AON_FabricIndirectConfigAccessAddress3);
	WREG32(data, ficaa_val);

	WREG32(address, smnDF_PIE_AON_FabricIndirectConfigAccessDataLo3);
	ficadl_val = RREG32(data);

	WREG32(address, smnDF_PIE_AON_FabricIndirectConfigAccessDataHi3);
	ficadh_val = RREG32(data);

	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);

	return (((ficadh_val & 0xFFFFFFFFFFFFFFFF) << 32) | ficadl_val);
}