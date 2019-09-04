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
struct TYPE_2__ {struct r600_audio_pin* pin; } ;
struct radeon_device {TYPE_1__ audio; } ;
struct r600_audio_pin {int dummy; } ;

/* Variables and functions */

struct r600_audio_pin *r600_audio_get_pin(struct radeon_device *rdev)
{
	/* only one pin on 6xx-NI */
	return &rdev->audio.pin[0];
}