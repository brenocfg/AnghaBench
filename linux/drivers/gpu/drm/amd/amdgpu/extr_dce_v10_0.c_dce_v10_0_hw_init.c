#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_pins; int /*<<< orphan*/ * pin; } ;
struct TYPE_5__ {TYPE_3__ audio; } ;
struct TYPE_4__ {int /*<<< orphan*/  default_dispclk; } ;
struct amdgpu_device {TYPE_2__ mode_info; TYPE_1__ clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_atombios_crtc_set_disp_eng_pll (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_init_dig (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v10_0_audio_enable (struct amdgpu_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dce_v10_0_hpd_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v10_0_init_golden_registers (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v10_0_pageflip_interrupt_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v10_0_set_vga_render_state (struct amdgpu_device*,int) ; 

__attribute__((used)) static int dce_v10_0_hw_init(void *handle)
{
	int i;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	dce_v10_0_init_golden_registers(adev);

	/* disable vga render */
	dce_v10_0_set_vga_render_state(adev, false);
	/* init dig PHYs, disp eng pll */
	amdgpu_atombios_encoder_init_dig(adev);
	amdgpu_atombios_crtc_set_disp_eng_pll(adev, adev->clock.default_dispclk);

	/* initialize hpd */
	dce_v10_0_hpd_init(adev);

	for (i = 0; i < adev->mode_info.audio.num_pins; i++) {
		dce_v10_0_audio_enable(adev, &adev->mode_info.audio.pin[i], false);
	}

	dce_v10_0_pageflip_interrupt_init(adev);

	return 0;
}