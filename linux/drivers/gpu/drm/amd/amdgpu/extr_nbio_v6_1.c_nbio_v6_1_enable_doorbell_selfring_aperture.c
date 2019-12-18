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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct amdgpu_device {TYPE_1__ doorbell; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL ; 
 int /*<<< orphan*/  DOORBELL_SELFRING_GPA_APER_EN ; 
 int /*<<< orphan*/  DOORBELL_SELFRING_GPA_APER_MODE ; 
 int /*<<< orphan*/  DOORBELL_SELFRING_GPA_APER_SIZE ; 
 int /*<<< orphan*/  NBIO ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_HIGH ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_LOW ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nbio_v6_1_enable_doorbell_selfring_aperture(struct amdgpu_device *adev,
							bool enable)
{
	u32 tmp = 0;

	if (enable) {
		tmp = REG_SET_FIELD(tmp, BIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL, DOORBELL_SELFRING_GPA_APER_EN, 1) |
		      REG_SET_FIELD(tmp, BIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL, DOORBELL_SELFRING_GPA_APER_MODE, 1) |
		      REG_SET_FIELD(tmp, BIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL, DOORBELL_SELFRING_GPA_APER_SIZE, 0);

		WREG32_SOC15(NBIO, 0, mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_LOW,
			     lower_32_bits(adev->doorbell.base));
		WREG32_SOC15(NBIO, 0, mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_HIGH,
			     upper_32_bits(adev->doorbell.base));
	}

	WREG32_SOC15(NBIO, 0, mmBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL, tmp);
}