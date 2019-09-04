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
struct TYPE_2__ {int active_encoders; } ;
struct radeon_device {TYPE_1__ mode_info; } ;

/* Variables and functions */

void radeon_atom_release_dig_encoder(struct radeon_device *rdev, int enc_idx)
{
	if (enc_idx < 0)
		return;
	rdev->mode_info.active_encoders &= ~(1 << enc_idx);
}