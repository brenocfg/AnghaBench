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
struct radeon_connector {int devices; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int ATOM_DEVICE_CRT1_SUPPORT ; 
 int ATOM_DEVICE_CRT2_SUPPORT ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 int ATOM_DEVICE_DFP1_SUPPORT ; 
 int ATOM_DEVICE_DFP2_SUPPORT ; 
 int ATOM_DEVICE_DFP3_SUPPORT ; 
 int ATOM_DEVICE_DFP4_SUPPORT ; 
 int ATOM_DEVICE_DFP5_SUPPORT ; 
 int ATOM_DEVICE_DFP6_SUPPORT ; 
 int ATOM_DEVICE_LCD1_SUPPORT ; 
 int ATOM_DEVICE_TV1_SUPPORT ; 
 int /*<<< orphan*/  ATOM_S0_CRT1_COLOR ; 
 int /*<<< orphan*/  ATOM_S0_CRT1_MASK ; 
 int /*<<< orphan*/  ATOM_S0_CRT2_COLOR ; 
 int /*<<< orphan*/  ATOM_S0_CRT2_MASK ; 
 int /*<<< orphan*/  ATOM_S0_CV_MASK ; 
 int /*<<< orphan*/  ATOM_S0_DFP1 ; 
 int /*<<< orphan*/  ATOM_S0_DFP2 ; 
 int /*<<< orphan*/  ATOM_S0_DFP3 ; 
 int /*<<< orphan*/  ATOM_S0_DFP4 ; 
 int /*<<< orphan*/  ATOM_S0_DFP5 ; 
 int /*<<< orphan*/  ATOM_S0_DFP6 ; 
 int /*<<< orphan*/  ATOM_S0_LCD1 ; 
 int /*<<< orphan*/  ATOM_S0_TV1_MASK ; 
 int /*<<< orphan*/  ATOM_S3_CRT1_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_CRT2_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_CV_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_DFP1_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_DFP2_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_DFP3_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_DFP4_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_DFP5_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_DFP6_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_LCD1_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S3_TV1_ACTIVE ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_CRT1 ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_CRT2 ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_CV ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_DFP1 ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_DFP2 ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_DFP3 ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_DFP4 ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_DFP5 ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_DFP6 ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_LCD1 ; 
 int /*<<< orphan*/  ATOM_S6_ACC_REQ_TV1 ; 
 scalar_t__ CHIP_R600 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  R600_BIOS_0_SCRATCH ; 
 int /*<<< orphan*/  R600_BIOS_3_SCRATCH ; 
 int /*<<< orphan*/  R600_BIOS_6_SCRATCH ; 
 int /*<<< orphan*/  RADEON_BIOS_0_SCRATCH ; 
 int /*<<< orphan*/  RADEON_BIOS_3_SCRATCH ; 
 int /*<<< orphan*/  RADEON_BIOS_6_SCRATCH ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void
radeon_atombios_connected_scratch_regs(struct drm_connector *connector,
				       struct drm_encoder *encoder,
				       bool connected)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_connector *radeon_connector =
	    to_radeon_connector(connector);
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint32_t bios_0_scratch, bios_3_scratch, bios_6_scratch;

	if (rdev->family >= CHIP_R600) {
		bios_0_scratch = RREG32(R600_BIOS_0_SCRATCH);
		bios_3_scratch = RREG32(R600_BIOS_3_SCRATCH);
		bios_6_scratch = RREG32(R600_BIOS_6_SCRATCH);
	} else {
		bios_0_scratch = RREG32(RADEON_BIOS_0_SCRATCH);
		bios_3_scratch = RREG32(RADEON_BIOS_3_SCRATCH);
		bios_6_scratch = RREG32(RADEON_BIOS_6_SCRATCH);
	}

	if ((radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_TV1_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("TV1 connected\n");
			bios_3_scratch |= ATOM_S3_TV1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_TV1;
		} else {
			DRM_DEBUG_KMS("TV1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_TV1_MASK;
			bios_3_scratch &= ~ATOM_S3_TV1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_TV1;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_CV_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CV_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("CV connected\n");
			bios_3_scratch |= ATOM_S3_CV_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_CV;
		} else {
			DRM_DEBUG_KMS("CV disconnected\n");
			bios_0_scratch &= ~ATOM_S0_CV_MASK;
			bios_3_scratch &= ~ATOM_S3_CV_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_CV;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_LCD1_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("LCD1 connected\n");
			bios_0_scratch |= ATOM_S0_LCD1;
			bios_3_scratch |= ATOM_S3_LCD1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_LCD1;
		} else {
			DRM_DEBUG_KMS("LCD1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_LCD1;
			bios_3_scratch &= ~ATOM_S3_LCD1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_LCD1;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CRT1_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("CRT1 connected\n");
			bios_0_scratch |= ATOM_S0_CRT1_COLOR;
			bios_3_scratch |= ATOM_S3_CRT1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_CRT1;
		} else {
			DRM_DEBUG_KMS("CRT1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_CRT1_MASK;
			bios_3_scratch &= ~ATOM_S3_CRT1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_CRT1;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CRT2_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("CRT2 connected\n");
			bios_0_scratch |= ATOM_S0_CRT2_COLOR;
			bios_3_scratch |= ATOM_S3_CRT2_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_CRT2;
		} else {
			DRM_DEBUG_KMS("CRT2 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_CRT2_MASK;
			bios_3_scratch &= ~ATOM_S3_CRT2_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_CRT2;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP1_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("DFP1 connected\n");
			bios_0_scratch |= ATOM_S0_DFP1;
			bios_3_scratch |= ATOM_S3_DFP1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP1;
		} else {
			DRM_DEBUG_KMS("DFP1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP1;
			bios_3_scratch &= ~ATOM_S3_DFP1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP1;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP2_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("DFP2 connected\n");
			bios_0_scratch |= ATOM_S0_DFP2;
			bios_3_scratch |= ATOM_S3_DFP2_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP2;
		} else {
			DRM_DEBUG_KMS("DFP2 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP2;
			bios_3_scratch &= ~ATOM_S3_DFP2_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP2;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_DFP3_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP3_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("DFP3 connected\n");
			bios_0_scratch |= ATOM_S0_DFP3;
			bios_3_scratch |= ATOM_S3_DFP3_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP3;
		} else {
			DRM_DEBUG_KMS("DFP3 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP3;
			bios_3_scratch &= ~ATOM_S3_DFP3_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP3;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_DFP4_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP4_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("DFP4 connected\n");
			bios_0_scratch |= ATOM_S0_DFP4;
			bios_3_scratch |= ATOM_S3_DFP4_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP4;
		} else {
			DRM_DEBUG_KMS("DFP4 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP4;
			bios_3_scratch &= ~ATOM_S3_DFP4_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP4;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_DFP5_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP5_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("DFP5 connected\n");
			bios_0_scratch |= ATOM_S0_DFP5;
			bios_3_scratch |= ATOM_S3_DFP5_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP5;
		} else {
			DRM_DEBUG_KMS("DFP5 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP5;
			bios_3_scratch &= ~ATOM_S3_DFP5_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP5;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_DFP6_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP6_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("DFP6 connected\n");
			bios_0_scratch |= ATOM_S0_DFP6;
			bios_3_scratch |= ATOM_S3_DFP6_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP6;
		} else {
			DRM_DEBUG_KMS("DFP6 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP6;
			bios_3_scratch &= ~ATOM_S3_DFP6_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP6;
		}
	}

	if (rdev->family >= CHIP_R600) {
		WREG32(R600_BIOS_0_SCRATCH, bios_0_scratch);
		WREG32(R600_BIOS_3_SCRATCH, bios_3_scratch);
		WREG32(R600_BIOS_6_SCRATCH, bios_6_scratch);
	} else {
		WREG32(RADEON_BIOS_0_SCRATCH, bios_0_scratch);
		WREG32(RADEON_BIOS_3_SCRATCH, bios_3_scratch);
		WREG32(RADEON_BIOS_6_SCRATCH, bios_6_scratch);
	}
}