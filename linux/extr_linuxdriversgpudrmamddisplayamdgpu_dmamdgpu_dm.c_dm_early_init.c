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
struct TYPE_2__ {int num_crtc; int num_hpd; int num_dig; int /*<<< orphan*/ * funcs; void* plane_type; } ;
struct amdgpu_device {int asic_type; TYPE_1__ mode_info; } ;

/* Variables and functions */
#define  CHIP_BONAIRE 143 
#define  CHIP_CARRIZO 142 
#define  CHIP_FIJI 141 
#define  CHIP_HAWAII 140 
#define  CHIP_KABINI 139 
#define  CHIP_KAVERI 138 
#define  CHIP_MULLINS 137 
#define  CHIP_POLARIS10 136 
#define  CHIP_POLARIS11 135 
#define  CHIP_POLARIS12 134 
#define  CHIP_STONEY 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_dm_set_irq_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dm_display_funcs ; 
 void* dm_plane_type_carizzo ; 
 void* dm_plane_type_default ; 
 void* dm_plane_type_stoney ; 

__attribute__((used)) static int dm_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	switch (adev->asic_type) {
	case CHIP_BONAIRE:
	case CHIP_HAWAII:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		adev->mode_info.plane_type = dm_plane_type_default;
		break;
	case CHIP_KAVERI:
		adev->mode_info.num_crtc = 4;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 7;
		adev->mode_info.plane_type = dm_plane_type_default;
		break;
	case CHIP_KABINI:
	case CHIP_MULLINS:
		adev->mode_info.num_crtc = 2;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		adev->mode_info.plane_type = dm_plane_type_default;
		break;
	case CHIP_FIJI:
	case CHIP_TONGA:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 7;
		adev->mode_info.plane_type = dm_plane_type_default;
		break;
	case CHIP_CARRIZO:
		adev->mode_info.num_crtc = 3;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 9;
		adev->mode_info.plane_type = dm_plane_type_carizzo;
		break;
	case CHIP_STONEY:
		adev->mode_info.num_crtc = 2;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 9;
		adev->mode_info.plane_type = dm_plane_type_stoney;
		break;
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
		adev->mode_info.num_crtc = 5;
		adev->mode_info.num_hpd = 5;
		adev->mode_info.num_dig = 5;
		adev->mode_info.plane_type = dm_plane_type_default;
		break;
	case CHIP_POLARIS10:
	case CHIP_VEGAM:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		adev->mode_info.plane_type = dm_plane_type_default;
		break;
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
		adev->mode_info.num_crtc = 6;
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		adev->mode_info.plane_type = dm_plane_type_default;
		break;
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case CHIP_RAVEN:
		adev->mode_info.num_crtc = 4;
		adev->mode_info.num_hpd = 4;
		adev->mode_info.num_dig = 4;
		adev->mode_info.plane_type = dm_plane_type_default;
		break;
#endif
	default:
		DRM_ERROR("Unsupported ASIC type: 0x%X\n", adev->asic_type);
		return -EINVAL;
	}

	amdgpu_dm_set_irq_funcs(adev);

	if (adev->mode_info.funcs == NULL)
		adev->mode_info.funcs = &dm_display_funcs;

	/* Note: Do NOT change adev->audio_endpt_rreg and
	 * adev->audio_endpt_wreg because they are initialised in
	 * amdgpu_device_init() */
#if defined(CONFIG_DEBUG_KERNEL_DC)
	device_create_file(
		adev->ddev->dev,
		&dev_attr_s3_debug);
#endif

	return 0;
}