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
 int R600_PM_NUMBER_OF_TC ; 
 int /*<<< orphan*/  R600_TD_DFLT ; 
 int /*<<< orphan*/ * r600_dtc ; 
 int /*<<< orphan*/  r600_select_td (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_set_tc (struct radeon_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r600_utc ; 

__attribute__((used)) static void rv6xx_program_tp(struct radeon_device *rdev)
{
	int i;

	for (i = 0; i < R600_PM_NUMBER_OF_TC; i++)
		r600_set_tc(rdev, i, r600_utc[i], r600_dtc[i]);

	r600_select_td(rdev, R600_TD_DFLT);
}