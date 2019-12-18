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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct amdgpu_device {int /*<<< orphan*/  pcie_idx_lock; TYPE_1__* nbio_funcs; } ;
struct TYPE_2__ {unsigned long (* get_pcie_index_offset ) (struct amdgpu_device*) ;unsigned long (* get_pcie_data_offset ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int RREG32 (unsigned long) ; 
 int /*<<< orphan*/  WREG32 (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long stub1 (struct amdgpu_device*) ; 
 unsigned long stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static u64 soc15_pcie_rreg64(struct amdgpu_device *adev, u32 reg)
{
	unsigned long flags, address, data;
	u64 r;
	address = adev->nbio_funcs->get_pcie_index_offset(adev);
	data = adev->nbio_funcs->get_pcie_data_offset(adev);

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	/* read low 32 bit */
	WREG32(address, reg);
	(void)RREG32(address);
	r = RREG32(data);

	/* read high 32 bit*/
	WREG32(address, reg + 4);
	(void)RREG32(address);
	r |= ((u64)RREG32(data) << 32);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
	return r;
}