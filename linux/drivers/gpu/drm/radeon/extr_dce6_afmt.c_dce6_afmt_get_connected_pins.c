#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int num_pins; TYPE_2__* pin; } ;
struct radeon_device {TYPE_1__ audio; } ;
struct TYPE_4__ {int offset; int connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZ_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT ; 
 int PORT_CONNECTIVITY_MASK ; 
 int PORT_CONNECTIVITY_SHIFT ; 
 int RREG32_ENDPOINT (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce6_afmt_get_connected_pins(struct radeon_device *rdev)
{
	int i;
	u32 offset, tmp;

	for (i = 0; i < rdev->audio.num_pins; i++) {
		offset = rdev->audio.pin[i].offset;
		tmp = RREG32_ENDPOINT(offset,
				      AZ_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT);
		if (((tmp & PORT_CONNECTIVITY_MASK) >> PORT_CONNECTIVITY_SHIFT) == 1)
			rdev->audio.pin[i].connected = false;
		else
			rdev->audio.pin[i].connected = true;
	}
}