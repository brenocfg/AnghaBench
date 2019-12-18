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
struct radeon_encoder {int devices; } ;
struct radeon_device {scalar_t__ family; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int ATOM_DEVICE_CRT1_SUPPORT ; 
 int ATOM_DEVICE_CRT2_SUPPORT ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 int ATOM_DEVICE_DFP1_SUPPORT ; 
 int ATOM_DEVICE_DFP2_SUPPORT ; 
 int ATOM_DEVICE_DFP3_SUPPORT ; 
 int ATOM_DEVICE_DFP4_SUPPORT ; 
 int ATOM_DEVICE_DFP5_SUPPORT ; 
 int ATOM_DEVICE_LCD1_SUPPORT ; 
 int ATOM_DEVICE_TV1_SUPPORT ; 
 int /*<<< orphan*/  ATOM_S2_CRT1_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_CRT2_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_CV_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_DFP1_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_DFP2_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_DFP3_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_DFP4_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_DFP5_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_LCD1_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_TV1_DPMS_STATE ; 
 scalar_t__ CHIP_R600 ; 
 int /*<<< orphan*/  R600_BIOS_2_SCRATCH ; 
 int /*<<< orphan*/  RADEON_BIOS_2_SCRATCH ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void
radeon_atombios_encoder_dpms_scratch_regs(struct drm_encoder *encoder, bool on)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint32_t bios_2_scratch;

	if (ASIC_IS_DCE4(rdev))
		return;

	if (rdev->family >= CHIP_R600)
		bios_2_scratch = RREG32(R600_BIOS_2_SCRATCH);
	else
		bios_2_scratch = RREG32(RADEON_BIOS_2_SCRATCH);

	if (radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_TV1_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_TV1_DPMS_STATE;
	}
	if (radeon_encoder->devices & ATOM_DEVICE_CV_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_CV_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_CV_DPMS_STATE;
	}
	if (radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_CRT1_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_CRT1_DPMS_STATE;
	}
	if (radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_CRT2_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_CRT2_DPMS_STATE;
	}
	if (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_LCD1_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_LCD1_DPMS_STATE;
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_DFP1_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_DFP1_DPMS_STATE;
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_DFP2_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_DFP2_DPMS_STATE;
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP3_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_DFP3_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_DFP3_DPMS_STATE;
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP4_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_DFP4_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_DFP4_DPMS_STATE;
	}
	if (radeon_encoder->devices & ATOM_DEVICE_DFP5_SUPPORT) {
		if (on)
			bios_2_scratch &= ~ATOM_S2_DFP5_DPMS_STATE;
		else
			bios_2_scratch |= ATOM_S2_DFP5_DPMS_STATE;
	}

	if (rdev->family >= CHIP_R600)
		WREG32(R600_BIOS_2_SCRATCH, bios_2_scratch);
	else
		WREG32(RADEON_BIOS_2_SCRATCH, bios_2_scratch);
}