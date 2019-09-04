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
struct TYPE_2__ {int num_hpd; int num_dig; int /*<<< orphan*/  num_crtc; } ;
struct amdgpu_device {int asic_type; TYPE_1__ mode_info; int /*<<< orphan*/ * audio_endpt_wreg; int /*<<< orphan*/ * audio_endpt_rreg; } ;

/* Variables and functions */
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int EINVAL ; 
 int /*<<< orphan*/  dce_v6_0_audio_endpt_rreg ; 
 int /*<<< orphan*/  dce_v6_0_audio_endpt_wreg ; 
 int /*<<< orphan*/  dce_v6_0_get_num_crtc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v6_0_set_display_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v6_0_set_irq_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int dce_v6_0_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	adev->audio_endpt_rreg = &dce_v6_0_audio_endpt_rreg;
	adev->audio_endpt_wreg = &dce_v6_0_audio_endpt_wreg;

	dce_v6_0_set_display_funcs(adev);

	adev->mode_info.num_crtc = dce_v6_0_get_num_crtc(adev);

	switch (adev->asic_type) {
	case CHIP_TAHITI:
	case CHIP_PITCAIRN:
	case CHIP_VERDE:
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		break;
	case CHIP_OLAND:
		adev->mode_info.num_hpd = 2;
		adev->mode_info.num_dig = 2;
		break;
	default:
		return -EINVAL;
	}

	dce_v6_0_set_irq_funcs(adev);

	return 0;
}