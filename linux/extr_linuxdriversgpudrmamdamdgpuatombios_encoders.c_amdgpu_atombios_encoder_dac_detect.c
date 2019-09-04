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
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_connector {int dummy; } ;
struct amdgpu_encoder {int /*<<< orphan*/  devices; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_connector {int devices; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int ATOM_DEVICE_CRT1_SUPPORT ; 
 int ATOM_DEVICE_CRT2_SUPPORT ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 int ATOM_DEVICE_TV1_SUPPORT ; 
 int ATOM_S0_CRT1_MASK ; 
 int ATOM_S0_CRT2_MASK ; 
 int ATOM_S0_CV_MASK ; 
 int ATOM_S0_CV_MASK_A ; 
 int ATOM_S0_TV1_COMPOSITE ; 
 int ATOM_S0_TV1_COMPOSITE_A ; 
 int ATOM_S0_TV1_SVIDEO ; 
 int ATOM_S0_TV1_SVIDEO_A ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_dac_load_detect (struct drm_encoder*,struct drm_connector*) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 int /*<<< orphan*/  mmBIOS_SCRATCH_0 ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

enum drm_connector_status
amdgpu_atombios_encoder_dac_detect(struct drm_encoder *encoder,
			    struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	uint32_t bios_0_scratch;

	if (!amdgpu_atombios_encoder_dac_load_detect(encoder, connector)) {
		DRM_DEBUG_KMS("detect returned false \n");
		return connector_status_unknown;
	}

	bios_0_scratch = RREG32(mmBIOS_SCRATCH_0);

	DRM_DEBUG_KMS("Bios 0 scratch %x %08x\n", bios_0_scratch, amdgpu_encoder->devices);
	if (amdgpu_connector->devices & ATOM_DEVICE_CRT1_SUPPORT) {
		if (bios_0_scratch & ATOM_S0_CRT1_MASK)
			return connector_status_connected;
	}
	if (amdgpu_connector->devices & ATOM_DEVICE_CRT2_SUPPORT) {
		if (bios_0_scratch & ATOM_S0_CRT2_MASK)
			return connector_status_connected;
	}
	if (amdgpu_connector->devices & ATOM_DEVICE_CV_SUPPORT) {
		if (bios_0_scratch & (ATOM_S0_CV_MASK|ATOM_S0_CV_MASK_A))
			return connector_status_connected;
	}
	if (amdgpu_connector->devices & ATOM_DEVICE_TV1_SUPPORT) {
		if (bios_0_scratch & (ATOM_S0_TV1_COMPOSITE | ATOM_S0_TV1_COMPOSITE_A))
			return connector_status_connected; /* CTV */
		else if (bios_0_scratch & (ATOM_S0_TV1_SVIDEO | ATOM_S0_TV1_SVIDEO_A))
			return connector_status_connected; /* STV */
	}
	return connector_status_disconnected;
}