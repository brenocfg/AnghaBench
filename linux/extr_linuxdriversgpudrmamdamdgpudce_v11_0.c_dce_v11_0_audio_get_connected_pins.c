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
typedef  int u32 ;
struct TYPE_5__ {int num_pins; TYPE_1__* pin; } ;
struct TYPE_6__ {TYPE_2__ audio; } ;
struct amdgpu_device {TYPE_3__ mode_info; } ;
struct TYPE_4__ {int offset; int connected; } ;

/* Variables and functions */
 int AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT__PORT_CONNECTIVITY_MASK ; 
 int AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT__PORT_CONNECTIVITY__SHIFT ; 
 int RREG32_AUDIO_ENDPT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixAZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT ; 

__attribute__((used)) static void dce_v11_0_audio_get_connected_pins(struct amdgpu_device *adev)
{
	int i;
	u32 offset, tmp;

	for (i = 0; i < adev->mode_info.audio.num_pins; i++) {
		offset = adev->mode_info.audio.pin[i].offset;
		tmp = RREG32_AUDIO_ENDPT(offset,
					 ixAZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT);
		if (((tmp &
		AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT__PORT_CONNECTIVITY_MASK) >>
		AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT__PORT_CONNECTIVITY__SHIFT) == 1)
			adev->mode_info.audio.pin[i].connected = false;
		else
			adev->mode_info.audio.pin[i].connected = true;
	}
}