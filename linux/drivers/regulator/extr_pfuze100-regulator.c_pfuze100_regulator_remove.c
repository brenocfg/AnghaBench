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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * pm_power_off_prepare ; 
 int /*<<< orphan*/ * syspm_pfuze_chip ; 

__attribute__((used)) static int pfuze100_regulator_remove(struct i2c_client *client)
{
	if (syspm_pfuze_chip) {
		syspm_pfuze_chip = NULL;
		pm_power_off_prepare = NULL;
	}

	return 0;
}