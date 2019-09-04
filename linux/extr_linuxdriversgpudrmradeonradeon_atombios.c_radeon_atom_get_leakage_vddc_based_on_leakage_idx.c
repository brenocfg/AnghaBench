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

/* Variables and functions */
 int /*<<< orphan*/  VOLTAGE_TYPE_VDDC ; 
 int radeon_atom_get_max_vddc (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int radeon_atom_get_leakage_vddc_based_on_leakage_idx(struct radeon_device *rdev,
						      u16 *voltage,
						      u16 leakage_idx)
{
	return radeon_atom_get_max_vddc(rdev, VOLTAGE_TYPE_VDDC, leakage_idx, voltage);
}