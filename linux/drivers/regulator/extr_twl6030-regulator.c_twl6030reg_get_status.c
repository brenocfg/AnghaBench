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
struct twlreg_info {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int REGULATOR_STATUS_NORMAL ; 
 int REGULATOR_STATUS_OFF ; 
 int REGULATOR_STATUS_STANDBY ; 
 int TWL6030_CFG_STATE_APP (int) ; 
#define  TWL6030_CFG_STATE_OFF 131 
#define  TWL6030_CFG_STATE_OFF2 130 
#define  TWL6030_CFG_STATE_ON 129 
#define  TWL6030_CFG_STATE_SLEEP 128 
 int /*<<< orphan*/  TWL_MODULE_PM_RECEIVER ; 
 int /*<<< orphan*/  VREG_STATE ; 
 struct twlreg_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int twlreg_grp (struct regulator_dev*) ; 
 int twlreg_read (struct twlreg_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030reg_get_status(struct regulator_dev *rdev)
{
	struct twlreg_info	*info = rdev_get_drvdata(rdev);
	int			val;

	val = twlreg_grp(rdev);
	if (val < 0)
		return val;

	val = twlreg_read(info, TWL_MODULE_PM_RECEIVER, VREG_STATE);

	switch (TWL6030_CFG_STATE_APP(val)) {
	case TWL6030_CFG_STATE_ON:
		return REGULATOR_STATUS_NORMAL;

	case TWL6030_CFG_STATE_SLEEP:
		return REGULATOR_STATUS_STANDBY;

	case TWL6030_CFG_STATE_OFF:
	case TWL6030_CFG_STATE_OFF2:
	default:
		break;
	}

	return REGULATOR_STATUS_OFF;
}