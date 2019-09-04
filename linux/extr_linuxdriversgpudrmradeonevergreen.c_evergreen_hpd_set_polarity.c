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
typedef  enum radeon_hpd_id { ____Placeholder_radeon_hpd_id } radeon_hpd_id ;

/* Variables and functions */
 int /*<<< orphan*/  DC_HPDx_INT_CONTROL (int) ; 
 int /*<<< orphan*/  DC_HPDx_INT_POLARITY ; 
 int RADEON_HPD_NONE ; 
 int /*<<< orphan*/  WREG32_AND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_OR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int evergreen_hpd_sense (struct radeon_device*,int) ; 

void evergreen_hpd_set_polarity(struct radeon_device *rdev,
				enum radeon_hpd_id hpd)
{
	bool connected = evergreen_hpd_sense(rdev, hpd);

	if (hpd == RADEON_HPD_NONE)
		return;

	if (connected)
		WREG32_AND(DC_HPDx_INT_CONTROL(hpd), ~DC_HPDx_INT_POLARITY);
	else
		WREG32_OR(DC_HPDx_INT_CONTROL(hpd), DC_HPDx_INT_POLARITY);
}