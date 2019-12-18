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
typedef  size_t u8 ;
struct regulator_dev {int dummy; } ;
struct max8660 {size_t* shadow_regs; } ;

/* Variables and functions */
 size_t MAX8660_ADTV2 ; 
 size_t MAX8660_SDTV2 ; 
 scalar_t__ MAX8660_V3 ; 
 struct max8660* rdev_get_drvdata (struct regulator_dev*) ; 
 scalar_t__ rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int max8660_dcdc_get_voltage_sel(struct regulator_dev *rdev)
{
	struct max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 reg = (rdev_get_id(rdev) == MAX8660_V3) ? MAX8660_ADTV2 : MAX8660_SDTV2;
	u8 selector = max8660->shadow_regs[reg];

	return selector;
}