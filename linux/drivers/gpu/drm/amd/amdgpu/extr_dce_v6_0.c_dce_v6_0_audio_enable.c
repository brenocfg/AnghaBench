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
struct amdgpu_device {int dummy; } ;
struct amdgpu_audio_pin {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL__AUDIO_ENABLED_MASK ; 
 int /*<<< orphan*/  WREG32_AUDIO_ENDPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixAZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL ; 

__attribute__((used)) static void dce_v6_0_audio_enable(struct amdgpu_device *adev,
				  struct amdgpu_audio_pin *pin,
				  bool enable)
{
	if (!pin)
		return;

	WREG32_AUDIO_ENDPT(pin->offset, ixAZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			enable ? AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL__AUDIO_ENABLED_MASK : 0);
}