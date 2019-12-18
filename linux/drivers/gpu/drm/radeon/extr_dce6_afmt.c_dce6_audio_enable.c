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
typedef  scalar_t__ u8 ;
struct radeon_device {int dummy; } ;
struct r600_audio_pin {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ENABLED ; 
 int /*<<< orphan*/  AZ_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL ; 
 int /*<<< orphan*/  WREG32_ENDPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce6_audio_enable(struct radeon_device *rdev,
		       struct r600_audio_pin *pin,
		       u8 enable_mask)
{
	if (!pin)
		return;

	WREG32_ENDPOINT(pin->offset, AZ_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			enable_mask ? AUDIO_ENABLED : 0);
}