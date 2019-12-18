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
typedef  int /*<<< orphan*/  uint32_t ;
struct cgs_device {int dummy; } ;
typedef  enum cgs_ind_reg { ____Placeholder_cgs_ind_reg } cgs_ind_reg ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_FUNC_ADEV ; 
#define  CGS_IND_REG_GC_CAC 135 
#define  CGS_IND_REG_SE_CAC 134 
#define  CGS_IND_REG__AUDIO_ENDPT 133 
#define  CGS_IND_REG__DIDT 132 
#define  CGS_IND_REG__MMIO 131 
#define  CGS_IND_REG__PCIE 130 
#define  CGS_IND_REG__SMC 129 
#define  CGS_IND_REG__UVD_CTX 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 void WREG32_DIDT (unsigned int,int /*<<< orphan*/ ) ; 
 void WREG32_GC_CAC (unsigned int,int /*<<< orphan*/ ) ; 
 void WREG32_IDX (unsigned int,int /*<<< orphan*/ ) ; 
 void WREG32_PCIE (unsigned int,int /*<<< orphan*/ ) ; 
 void WREG32_SE_CAC (unsigned int,int /*<<< orphan*/ ) ; 
 void WREG32_SMC (unsigned int,int /*<<< orphan*/ ) ; 
 void WREG32_UVD_CTX (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_cgs_write_ind_register(struct cgs_device *cgs_device,
					  enum cgs_ind_reg space,
					  unsigned index, uint32_t value)
{
	CGS_FUNC_ADEV;
	switch (space) {
	case CGS_IND_REG__MMIO:
		return WREG32_IDX(index, value);
	case CGS_IND_REG__PCIE:
		return WREG32_PCIE(index, value);
	case CGS_IND_REG__SMC:
		return WREG32_SMC(index, value);
	case CGS_IND_REG__UVD_CTX:
		return WREG32_UVD_CTX(index, value);
	case CGS_IND_REG__DIDT:
		return WREG32_DIDT(index, value);
	case CGS_IND_REG_GC_CAC:
		return WREG32_GC_CAC(index, value);
	case CGS_IND_REG_SE_CAC:
		return WREG32_SE_CAC(index, value);
	case CGS_IND_REG__AUDIO_ENDPT:
		DRM_ERROR("audio endpt register access not implemented.\n");
		return;
	}
	WARN(1, "Invalid indirect register space");
}