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
struct tm2_touchkey_data {int /*<<< orphan*/  regulators; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tm2_touchkey_power_enable(struct tm2_touchkey_data *touchkey)
{
	int error;

	error = regulator_bulk_enable(ARRAY_SIZE(touchkey->regulators),
				      touchkey->regulators);
	if (error)
		return error;

	/* waiting for device initialization, at least 150ms */
	msleep(150);

	return 0;
}