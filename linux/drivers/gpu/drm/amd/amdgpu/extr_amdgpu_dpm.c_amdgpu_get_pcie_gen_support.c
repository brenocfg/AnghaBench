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
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_pcie_gen { ____Placeholder_amdgpu_pcie_gen } amdgpu_pcie_gen ;

/* Variables and functions */
#define  AMDGPU_PCIE_GEN1 130 
#define  AMDGPU_PCIE_GEN2 129 
#define  AMDGPU_PCIE_GEN3 128 
 int CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 ; 
 int CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3 ; 

enum amdgpu_pcie_gen amdgpu_get_pcie_gen_support(struct amdgpu_device *adev,
						 u32 sys_mask,
						 enum amdgpu_pcie_gen asic_gen,
						 enum amdgpu_pcie_gen default_gen)
{
	switch (asic_gen) {
	case AMDGPU_PCIE_GEN1:
		return AMDGPU_PCIE_GEN1;
	case AMDGPU_PCIE_GEN2:
		return AMDGPU_PCIE_GEN2;
	case AMDGPU_PCIE_GEN3:
		return AMDGPU_PCIE_GEN3;
	default:
		if ((sys_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3) &&
		    (default_gen == AMDGPU_PCIE_GEN3))
			return AMDGPU_PCIE_GEN3;
		else if ((sys_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2) &&
			 (default_gen == AMDGPU_PCIE_GEN2))
			return AMDGPU_PCIE_GEN2;
		else
			return AMDGPU_PCIE_GEN1;
	}
	return AMDGPU_PCIE_GEN1;
}