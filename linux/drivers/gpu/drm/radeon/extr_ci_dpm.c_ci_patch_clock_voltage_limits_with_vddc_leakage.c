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
typedef  int /*<<< orphan*/  u16 ;
struct radeon_device {int dummy; } ;
struct radeon_clock_and_voltage_limits {int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_patch_with_vddc_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci_patch_with_vddci_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ci_patch_clock_voltage_limits_with_vddc_leakage(struct radeon_device *rdev,
							    struct radeon_clock_and_voltage_limits *table)
{
	if (table) {
		ci_patch_with_vddc_leakage(rdev, (u16 *)&table->vddc);
		ci_patch_with_vddci_leakage(rdev, (u16 *)&table->vddci);
	}
}