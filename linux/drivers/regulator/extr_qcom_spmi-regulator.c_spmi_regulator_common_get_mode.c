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
typedef  int u8 ;
struct spmi_regulator {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
#define  SPMI_COMMON_MODE_AUTO_MASK 129 
#define  SPMI_COMMON_MODE_HPM_MASK 128 
 int /*<<< orphan*/  SPMI_COMMON_REG_MODE ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int /*<<< orphan*/  spmi_vreg_read (struct spmi_regulator*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static unsigned int spmi_regulator_common_get_mode(struct regulator_dev *rdev)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 reg;

	spmi_vreg_read(vreg, SPMI_COMMON_REG_MODE, &reg, 1);

	reg &= SPMI_COMMON_MODE_HPM_MASK | SPMI_COMMON_MODE_AUTO_MASK;

	switch (reg) {
	case SPMI_COMMON_MODE_HPM_MASK:
		return REGULATOR_MODE_NORMAL;
	case SPMI_COMMON_MODE_AUTO_MASK:
		return REGULATOR_MODE_FAST;
	default:
		return REGULATOR_MODE_IDLE;
	}
}