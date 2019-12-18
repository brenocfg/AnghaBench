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
struct TYPE_2__ {int enabled; int num_pins; int /*<<< orphan*/ * pin; } ;
struct radeon_device {TYPE_1__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_audio_enable (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void radeon_audio_fini(struct radeon_device *rdev)
{
	int i;

	if (!rdev->audio.enabled)
		return;

	for (i = 0; i < rdev->audio.num_pins; i++)
		radeon_audio_enable(rdev, &rdev->audio.pin[i], 0);

	rdev->audio.enabled = false;
}