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
struct TYPE_3__ {int enabled; int num_pins; TYPE_2__* pin; } ;
struct radeon_device {TYPE_1__ audio; } ;
struct TYPE_4__ {int channels; int rate; int bits_per_sample; int connected; int id; int /*<<< orphan*/  offset; scalar_t__ category_code; scalar_t__ status_bits; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE61 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE64 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE8 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE81 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE83 (struct radeon_device*) ; 
 int /*<<< orphan*/ * pin_offsets ; 
 int /*<<< orphan*/  radeon_audio ; 
 int /*<<< orphan*/  radeon_audio_chipset_supported (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_audio_enable (struct radeon_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_audio_interface_init (struct radeon_device*) ; 

int radeon_audio_init(struct radeon_device *rdev)
{
	int i;

	if (!radeon_audio || !radeon_audio_chipset_supported(rdev))
		return 0;

	rdev->audio.enabled = true;

	if (ASIC_IS_DCE83(rdev))		/* KB: 2 streams, 3 endpoints */
		rdev->audio.num_pins = 3;
	else if (ASIC_IS_DCE81(rdev))	/* KV: 4 streams, 7 endpoints */
		rdev->audio.num_pins = 7;
	else if (ASIC_IS_DCE8(rdev))	/* BN/HW: 6 streams, 7 endpoints */
		rdev->audio.num_pins = 7;
	else if (ASIC_IS_DCE64(rdev))	/* OL: 2 streams, 2 endpoints */
		rdev->audio.num_pins = 2;
	else if (ASIC_IS_DCE61(rdev))	/* TN: 4 streams, 6 endpoints */
		rdev->audio.num_pins = 6;
	else if (ASIC_IS_DCE6(rdev))	/* SI: 6 streams, 6 endpoints */
		rdev->audio.num_pins = 6;
	else
		rdev->audio.num_pins = 1;

	for (i = 0; i < rdev->audio.num_pins; i++) {
		rdev->audio.pin[i].channels = -1;
		rdev->audio.pin[i].rate = -1;
		rdev->audio.pin[i].bits_per_sample = -1;
		rdev->audio.pin[i].status_bits = 0;
		rdev->audio.pin[i].category_code = 0;
		rdev->audio.pin[i].connected = false;
		rdev->audio.pin[i].offset = pin_offsets[i];
		rdev->audio.pin[i].id = i;
	}

	radeon_audio_interface_init(rdev);

	/* disable audio.  it will be set up later */
	for (i = 0; i < rdev->audio.num_pins; i++)
		radeon_audio_enable(rdev, &rdev->audio.pin[i], 0);

	return 0;
}