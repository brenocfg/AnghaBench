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
struct radeon_device {int dummy; } ;
struct radeon_connector {int devices; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int ATOM_DEVICE_CRT1_SUPPORT ; 
 int ATOM_DEVICE_CRT2_SUPPORT ; 
 int ATOM_DEVICE_DFP1_SUPPORT ; 
 int ATOM_DEVICE_DFP2_SUPPORT ; 
 int ATOM_DEVICE_LCD1_SUPPORT ; 
 int ATOM_DEVICE_TV1_SUPPORT ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  RADEON_ACC_REQ_CRT1 ; 
 int /*<<< orphan*/  RADEON_ACC_REQ_CRT2 ; 
 int /*<<< orphan*/  RADEON_ACC_REQ_DFP1 ; 
 int /*<<< orphan*/  RADEON_ACC_REQ_DFP2 ; 
 int /*<<< orphan*/  RADEON_ACC_REQ_LCD1 ; 
 int /*<<< orphan*/  RADEON_ACC_REQ_TV1 ; 
 int /*<<< orphan*/  RADEON_BIOS_4_SCRATCH ; 
 int /*<<< orphan*/  RADEON_BIOS_5_SCRATCH ; 
 int /*<<< orphan*/  RADEON_CRT1_ATTACHED_COLOR ; 
 int /*<<< orphan*/  RADEON_CRT1_ATTACHED_MASK ; 
 int /*<<< orphan*/  RADEON_CRT1_ON ; 
 int /*<<< orphan*/  RADEON_CRT2_ATTACHED_COLOR ; 
 int /*<<< orphan*/  RADEON_CRT2_ATTACHED_MASK ; 
 int /*<<< orphan*/  RADEON_CRT2_ON ; 
 int /*<<< orphan*/  RADEON_DFP1_ATTACHED ; 
 int /*<<< orphan*/  RADEON_DFP1_ON ; 
 int /*<<< orphan*/  RADEON_DFP2_ATTACHED ; 
 int /*<<< orphan*/  RADEON_DFP2_ON ; 
 int /*<<< orphan*/  RADEON_LCD1_ATTACHED ; 
 int /*<<< orphan*/  RADEON_LCD1_ON ; 
 int /*<<< orphan*/  RADEON_TV1_ATTACHED_MASK ; 
 int /*<<< orphan*/  RADEON_TV1_ATTACHED_SVIDEO ; 
 int /*<<< orphan*/  RADEON_TV1_ON ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void
radeon_combios_connected_scratch_regs(struct drm_connector *connector,
				      struct drm_encoder *encoder,
				      bool connected)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_connector *radeon_connector =
	    to_radeon_connector(connector);
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint32_t bios_4_scratch = RREG32(RADEON_BIOS_4_SCRATCH);
	uint32_t bios_5_scratch = RREG32(RADEON_BIOS_5_SCRATCH);

	if ((radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_TV1_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("TV1 connected\n");
			/* fix me */
			bios_4_scratch |= RADEON_TV1_ATTACHED_SVIDEO;
			/*save->bios_4_scratch |= RADEON_TV1_ATTACHED_COMP; */
			bios_5_scratch |= RADEON_TV1_ON;
			bios_5_scratch |= RADEON_ACC_REQ_TV1;
		} else {
			DRM_DEBUG_KMS("TV1 disconnected\n");
			bios_4_scratch &= ~RADEON_TV1_ATTACHED_MASK;
			bios_5_scratch &= ~RADEON_TV1_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_TV1;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_LCD1_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("LCD1 connected\n");
			bios_4_scratch |= RADEON_LCD1_ATTACHED;
			bios_5_scratch |= RADEON_LCD1_ON;
			bios_5_scratch |= RADEON_ACC_REQ_LCD1;
		} else {
			DRM_DEBUG_KMS("LCD1 disconnected\n");
			bios_4_scratch &= ~RADEON_LCD1_ATTACHED;
			bios_5_scratch &= ~RADEON_LCD1_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_LCD1;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CRT1_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("CRT1 connected\n");
			bios_4_scratch |= RADEON_CRT1_ATTACHED_COLOR;
			bios_5_scratch |= RADEON_CRT1_ON;
			bios_5_scratch |= RADEON_ACC_REQ_CRT1;
		} else {
			DRM_DEBUG_KMS("CRT1 disconnected\n");
			bios_4_scratch &= ~RADEON_CRT1_ATTACHED_MASK;
			bios_5_scratch &= ~RADEON_CRT1_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_CRT1;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CRT2_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("CRT2 connected\n");
			bios_4_scratch |= RADEON_CRT2_ATTACHED_COLOR;
			bios_5_scratch |= RADEON_CRT2_ON;
			bios_5_scratch |= RADEON_ACC_REQ_CRT2;
		} else {
			DRM_DEBUG_KMS("CRT2 disconnected\n");
			bios_4_scratch &= ~RADEON_CRT2_ATTACHED_MASK;
			bios_5_scratch &= ~RADEON_CRT2_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_CRT2;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP1_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("DFP1 connected\n");
			bios_4_scratch |= RADEON_DFP1_ATTACHED;
			bios_5_scratch |= RADEON_DFP1_ON;
			bios_5_scratch |= RADEON_ACC_REQ_DFP1;
		} else {
			DRM_DEBUG_KMS("DFP1 disconnected\n");
			bios_4_scratch &= ~RADEON_DFP1_ATTACHED;
			bios_5_scratch &= ~RADEON_DFP1_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_DFP1;
		}
	}
	if ((radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP2_SUPPORT)) {
		if (connected) {
			DRM_DEBUG_KMS("DFP2 connected\n");
			bios_4_scratch |= RADEON_DFP2_ATTACHED;
			bios_5_scratch |= RADEON_DFP2_ON;
			bios_5_scratch |= RADEON_ACC_REQ_DFP2;
		} else {
			DRM_DEBUG_KMS("DFP2 disconnected\n");
			bios_4_scratch &= ~RADEON_DFP2_ATTACHED;
			bios_5_scratch &= ~RADEON_DFP2_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_DFP2;
		}
	}
	WREG32(RADEON_BIOS_4_SCRATCH, bios_4_scratch);
	WREG32(RADEON_BIOS_5_SCRATCH, bios_5_scratch);
}