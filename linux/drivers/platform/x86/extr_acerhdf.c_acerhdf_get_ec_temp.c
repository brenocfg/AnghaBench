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
struct thermal_zone_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acerhdf_check_param (struct thermal_zone_device*) ; 
 int acerhdf_get_temp (int*) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int acerhdf_get_ec_temp(struct thermal_zone_device *thermal, int *t)
{
	int temp, err = 0;

	acerhdf_check_param(thermal);

	err = acerhdf_get_temp(&temp);
	if (err)
		return err;

	if (verbose)
		pr_notice("temp %d\n", temp);

	*t = temp;
	return 0;
}