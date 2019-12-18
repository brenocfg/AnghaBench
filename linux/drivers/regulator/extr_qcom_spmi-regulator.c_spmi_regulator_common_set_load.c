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
struct spmi_regulator {int hpm_min_load; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int spmi_regulator_common_set_mode (struct regulator_dev*,unsigned int) ; 

__attribute__((used)) static int
spmi_regulator_common_set_load(struct regulator_dev *rdev, int load_uA)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	unsigned int mode;

	if (load_uA >= vreg->hpm_min_load)
		mode = REGULATOR_MODE_NORMAL;
	else
		mode = REGULATOR_MODE_IDLE;

	return spmi_regulator_common_set_mode(rdev, mode);
}