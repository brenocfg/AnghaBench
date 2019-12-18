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
typedef  enum ta_ras_block { ____Placeholder_ta_ras_block } ta_ras_block ;
typedef  enum amdgpu_ras_block { ____Placeholder_amdgpu_ras_block } amdgpu_ras_block ;

/* Variables and functions */
#define  AMDGPU_RAS_BLOCK__ATHUB 141 
#define  AMDGPU_RAS_BLOCK__DF 140 
#define  AMDGPU_RAS_BLOCK__FUSE 139 
#define  AMDGPU_RAS_BLOCK__GFX 138 
#define  AMDGPU_RAS_BLOCK__HDP 137 
#define  AMDGPU_RAS_BLOCK__MMHUB 136 
#define  AMDGPU_RAS_BLOCK__MP0 135 
#define  AMDGPU_RAS_BLOCK__MP1 134 
#define  AMDGPU_RAS_BLOCK__PCIE_BIF 133 
#define  AMDGPU_RAS_BLOCK__SDMA 132 
#define  AMDGPU_RAS_BLOCK__SEM 131 
#define  AMDGPU_RAS_BLOCK__SMN 130 
#define  AMDGPU_RAS_BLOCK__UMC 129 
#define  AMDGPU_RAS_BLOCK__XGMI_WAFL 128 
 int TA_RAS_BLOCK__ATHUB ; 
 int TA_RAS_BLOCK__DF ; 
 int TA_RAS_BLOCK__FUSE ; 
 int TA_RAS_BLOCK__GFX ; 
 int TA_RAS_BLOCK__HDP ; 
 int TA_RAS_BLOCK__MMHUB ; 
 int TA_RAS_BLOCK__MP0 ; 
 int TA_RAS_BLOCK__MP1 ; 
 int TA_RAS_BLOCK__PCIE_BIF ; 
 int TA_RAS_BLOCK__SDMA ; 
 int TA_RAS_BLOCK__SEM ; 
 int TA_RAS_BLOCK__SMN ; 
 int TA_RAS_BLOCK__UMC ; 
 int TA_RAS_BLOCK__XGMI_WAFL ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static inline enum ta_ras_block
amdgpu_ras_block_to_ta(enum amdgpu_ras_block block) {
	switch (block) {
	case AMDGPU_RAS_BLOCK__UMC:
		return TA_RAS_BLOCK__UMC;
	case AMDGPU_RAS_BLOCK__SDMA:
		return TA_RAS_BLOCK__SDMA;
	case AMDGPU_RAS_BLOCK__GFX:
		return TA_RAS_BLOCK__GFX;
	case AMDGPU_RAS_BLOCK__MMHUB:
		return TA_RAS_BLOCK__MMHUB;
	case AMDGPU_RAS_BLOCK__ATHUB:
		return TA_RAS_BLOCK__ATHUB;
	case AMDGPU_RAS_BLOCK__PCIE_BIF:
		return TA_RAS_BLOCK__PCIE_BIF;
	case AMDGPU_RAS_BLOCK__HDP:
		return TA_RAS_BLOCK__HDP;
	case AMDGPU_RAS_BLOCK__XGMI_WAFL:
		return TA_RAS_BLOCK__XGMI_WAFL;
	case AMDGPU_RAS_BLOCK__DF:
		return TA_RAS_BLOCK__DF;
	case AMDGPU_RAS_BLOCK__SMN:
		return TA_RAS_BLOCK__SMN;
	case AMDGPU_RAS_BLOCK__SEM:
		return TA_RAS_BLOCK__SEM;
	case AMDGPU_RAS_BLOCK__MP0:
		return TA_RAS_BLOCK__MP0;
	case AMDGPU_RAS_BLOCK__MP1:
		return TA_RAS_BLOCK__MP1;
	case AMDGPU_RAS_BLOCK__FUSE:
		return TA_RAS_BLOCK__FUSE;
	default:
		WARN_ONCE(1, "RAS ERROR: unexpected block id %d\n", block);
		return TA_RAS_BLOCK__UMC;
	}
}