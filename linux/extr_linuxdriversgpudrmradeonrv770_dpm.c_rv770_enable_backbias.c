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
 int BACKBIAS_PAD_EN ; 
 int BACKBIAS_VALUE ; 
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 

void rv770_enable_backbias(struct radeon_device *rdev,
			   bool enable)
{
	if (enable)
		WREG32_P(GENERAL_PWRMGT, BACKBIAS_PAD_EN, ~BACKBIAS_PAD_EN);
	else
		WREG32_P(GENERAL_PWRMGT, 0, ~(BACKBIAS_VALUE | BACKBIAS_PAD_EN));
}