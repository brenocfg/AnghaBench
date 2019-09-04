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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE2 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_NODCE (struct radeon_device*) ; 

__attribute__((used)) static int radeon_audio_chipset_supported(struct radeon_device *rdev)
{
	return ASIC_IS_DCE2(rdev) && !ASIC_IS_NODCE(rdev);
}