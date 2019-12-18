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
struct wm8350 {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8350_CS1_FLASH_MODE ; 
 int WM8350_CS1_ON_RAMP_MASK ; 
 int /*<<< orphan*/  WM8350_CSA_FLASH_CONTROL ; 
 int /*<<< orphan*/  WM8350_CSB_FLASH_CONTROL ; 
#define  WM8350_ISINK_A 129 
#define  WM8350_ISINK_B 128 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_isink_enable_time(struct regulator_dev *rdev)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int isink = rdev_get_id(rdev);
	int reg;

	switch (isink) {
	case WM8350_ISINK_A:
		reg = wm8350_reg_read(wm8350, WM8350_CSA_FLASH_CONTROL);
		break;
	case WM8350_ISINK_B:
		reg = wm8350_reg_read(wm8350, WM8350_CSB_FLASH_CONTROL);
		break;
	default:
		return -EINVAL;
	}

	if (reg & WM8350_CS1_FLASH_MODE) {
		switch (reg & WM8350_CS1_ON_RAMP_MASK) {
		case 0:
			return 0;
		case 1:
			return 1950;
		case 2:
			return 3910;
		case 3:
			return 7800;
		}
	} else {
		switch (reg & WM8350_CS1_ON_RAMP_MASK) {
		case 0:
			return 0;
		case 1:
			return 250000;
		case 2:
			return 500000;
		case 3:
			return 1000000;
		}
	}

	return -EINVAL;
}