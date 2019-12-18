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
struct drm_encoder {int dummy; } ;
struct amdgpu_encoder {int encoder_id; int /*<<< orphan*/  active_device; int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  DRM_MODE_DPMS_OFF 137 
#define  DRM_MODE_DPMS_ON 136 
#define  DRM_MODE_DPMS_STANDBY 135 
#define  DRM_MODE_DPMS_SUSPEND 134 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1 133 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 132 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY3 128 
 int /*<<< orphan*/  amdgpu_atombios_encoder_setup_dac (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_setup_dig (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_setup_dvo (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

void
amdgpu_atombios_encoder_dpms(struct drm_encoder *encoder, int mode)
{
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);

	DRM_DEBUG_KMS("encoder dpms %d to mode %d, devices %08x, active_devices %08x\n",
		  amdgpu_encoder->encoder_id, mode, amdgpu_encoder->devices,
		  amdgpu_encoder->active_device);
	switch (amdgpu_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		switch (mode) {
		case DRM_MODE_DPMS_ON:
			amdgpu_atombios_encoder_setup_dig(encoder, ATOM_ENABLE);
			break;
		case DRM_MODE_DPMS_STANDBY:
		case DRM_MODE_DPMS_SUSPEND:
		case DRM_MODE_DPMS_OFF:
			amdgpu_atombios_encoder_setup_dig(encoder, ATOM_DISABLE);
			break;
		}
		break;
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		switch (mode) {
		case DRM_MODE_DPMS_ON:
			amdgpu_atombios_encoder_setup_dvo(encoder, ATOM_ENABLE);
			break;
		case DRM_MODE_DPMS_STANDBY:
		case DRM_MODE_DPMS_SUSPEND:
		case DRM_MODE_DPMS_OFF:
			amdgpu_atombios_encoder_setup_dvo(encoder, ATOM_DISABLE);
			break;
		}
		break;
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
		switch (mode) {
		case DRM_MODE_DPMS_ON:
			amdgpu_atombios_encoder_setup_dac(encoder, ATOM_ENABLE);
			break;
		case DRM_MODE_DPMS_STANDBY:
		case DRM_MODE_DPMS_SUSPEND:
		case DRM_MODE_DPMS_OFF:
			amdgpu_atombios_encoder_setup_dac(encoder, ATOM_DISABLE);
			break;
		}
		break;
	default:
		return;
	}
}