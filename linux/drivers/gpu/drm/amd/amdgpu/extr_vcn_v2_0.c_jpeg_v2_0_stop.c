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
typedef  int uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT ; 
 int JPEG_CGC_CTRL__CLK_OFF_DELAY__SHIFT ; 
 int JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT ; 
 int JPEG_CGC_GATE__JMCIF_MASK ; 
 int JPEG_CGC_GATE__JPEG2_DEC_MASK ; 
 int JPEG_CGC_GATE__JPEG_DEC_MASK ; 
 int JPEG_CGC_GATE__JPEG_ENC_MASK ; 
 int JPEG_CGC_GATE__JRBBM_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_WAIT_ON_RREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  UVD_JMI_CNTL__SOFT_RESET_MASK ; 
 int UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK ; 
 int UVD_PGFSM_CONFIG__UVDJ_PWR_CONFIG__SHIFT ; 
 int /*<<< orphan*/  UVD_PGFSM_STATUS__UVDJ_PWR_STATUS_MASK ; 
 int UVD_PGFSM_STATUS__UVDJ_PWR_STATUS__SHIFT ; 
 int /*<<< orphan*/  VCN ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmJPEG_CGC_CTRL ; 
 int /*<<< orphan*/  mmJPEG_CGC_GATE ; 
 int /*<<< orphan*/  mmUVD_JMI_CNTL ; 
 int /*<<< orphan*/  mmUVD_JPEG_POWER_STATUS ; 
 int /*<<< orphan*/  mmUVD_PGFSM_CONFIG ; 
 int /*<<< orphan*/  mmUVD_PGFSM_STATUS ; 

__attribute__((used)) static int jpeg_v2_0_stop(struct amdgpu_device *adev)
{
	uint32_t tmp;
	int r = 0;

	/* reset JMI */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_JMI_CNTL),
		UVD_JMI_CNTL__SOFT_RESET_MASK,
		~UVD_JMI_CNTL__SOFT_RESET_MASK);

	/* enable JPEG CGC */
	tmp = RREG32_SOC15(VCN, 0, mmJPEG_CGC_CTRL);
	tmp |= 1 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	tmp |= 1 << JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	tmp |= 4 << JPEG_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(VCN, 0, mmJPEG_CGC_CTRL, tmp);


	tmp = RREG32_SOC15(VCN, 0, mmJPEG_CGC_GATE);
	tmp |= (JPEG_CGC_GATE__JPEG_DEC_MASK
		|JPEG_CGC_GATE__JPEG2_DEC_MASK
		|JPEG_CGC_GATE__JPEG_ENC_MASK
		|JPEG_CGC_GATE__JMCIF_MASK
		|JPEG_CGC_GATE__JRBBM_MASK);
	WREG32_SOC15(VCN, 0, mmJPEG_CGC_GATE, tmp);

	/* enable power gating */
	tmp = RREG32(SOC15_REG_OFFSET(UVD, 0, mmUVD_JPEG_POWER_STATUS));
	tmp &= ~UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK;
	tmp |=  0x1; //UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_TILES_OFF;
	WREG32(SOC15_REG_OFFSET(UVD, 0, mmUVD_JPEG_POWER_STATUS), tmp);

	tmp = 2 << UVD_PGFSM_CONFIG__UVDJ_PWR_CONFIG__SHIFT;
	WREG32(SOC15_REG_OFFSET(UVD, 0, mmUVD_PGFSM_CONFIG), tmp);

	SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_PGFSM_STATUS,
		(2 << UVD_PGFSM_STATUS__UVDJ_PWR_STATUS__SHIFT),
		UVD_PGFSM_STATUS__UVDJ_PWR_STATUS_MASK, r);

	if (r) {
		DRM_ERROR("amdgpu: JPEG enable power gating failed\n");
		return r;
	}

	return r;
}