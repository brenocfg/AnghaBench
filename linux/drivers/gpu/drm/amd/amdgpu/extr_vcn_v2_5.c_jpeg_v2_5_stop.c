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
typedef  int uint32_t ;
struct TYPE_2__ {int num_vcn_inst; int harvest_config; } ;
struct amdgpu_device {TYPE_1__ vcn; } ;

/* Variables and functions */
 int JPEG_CGC_GATE__JMCIF_MASK ; 
 int JPEG_CGC_GATE__JPEG2_DEC_MASK ; 
 int JPEG_CGC_GATE__JPEG_DEC_MASK ; 
 int JPEG_CGC_GATE__JRBBM_MASK ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  UVD_JMI_CNTL__SOFT_RESET_MASK ; 
 int /*<<< orphan*/  UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK ; 
 int /*<<< orphan*/  VCN ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmJPEG_CGC_GATE ; 
 int /*<<< orphan*/  mmUVD_JMI_CNTL ; 
 int /*<<< orphan*/  mmUVD_JPEG_POWER_STATUS ; 

__attribute__((used)) static int jpeg_v2_5_stop(struct amdgpu_device *adev)
{
	uint32_t tmp;
	int i;

	for (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.harvest_config & (1 << i))
			continue;
		/* reset JMI */
		WREG32_P(SOC15_REG_OFFSET(UVD, i, mmUVD_JMI_CNTL),
			UVD_JMI_CNTL__SOFT_RESET_MASK,
			~UVD_JMI_CNTL__SOFT_RESET_MASK);

		tmp = RREG32_SOC15(VCN, i, mmJPEG_CGC_GATE);
		tmp |= (JPEG_CGC_GATE__JPEG_DEC_MASK
			|JPEG_CGC_GATE__JPEG2_DEC_MASK
			|JPEG_CGC_GATE__JMCIF_MASK
			|JPEG_CGC_GATE__JRBBM_MASK);
		WREG32_SOC15(VCN, i, mmJPEG_CGC_GATE, tmp);

		/* enable anti hang mechanism */
		WREG32_P(SOC15_REG_OFFSET(UVD, i, mmUVD_JPEG_POWER_STATUS),
			UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK,
			~UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK);
	}

	return 0;
}