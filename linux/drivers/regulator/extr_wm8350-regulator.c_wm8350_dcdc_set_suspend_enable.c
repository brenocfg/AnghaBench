#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int dcdc1_hib_mode; int dcdc3_hib_mode; int dcdc4_hib_mode; int dcdc6_hib_mode; } ;
struct wm8350 {TYPE_1__ pmic; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8350_DCDC1_LOW_POWER ; 
 int /*<<< orphan*/  WM8350_DCDC3_LOW_POWER ; 
 int /*<<< orphan*/  WM8350_DCDC4_LOW_POWER ; 
 int /*<<< orphan*/  WM8350_DCDC6_LOW_POWER ; 
#define  WM8350_DCDC_1 133 
#define  WM8350_DCDC_2 132 
#define  WM8350_DCDC_3 131 
#define  WM8350_DCDC_4 130 
#define  WM8350_DCDC_5 129 
#define  WM8350_DCDC_6 128 
 int WM8350_DCDC_HIB_MODE_MASK ; 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8350_dcdc_set_suspend_enable(struct regulator_dev *rdev)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int dcdc = rdev_get_id(rdev);
	u16 val;

	switch (dcdc) {
	case WM8350_DCDC_1:
		val = wm8350_reg_read(wm8350, WM8350_DCDC1_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC1_LOW_POWER,
			val | wm8350->pmic.dcdc1_hib_mode);
		break;
	case WM8350_DCDC_3:
		val = wm8350_reg_read(wm8350, WM8350_DCDC3_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC3_LOW_POWER,
			val | wm8350->pmic.dcdc3_hib_mode);
		break;
	case WM8350_DCDC_4:
		val = wm8350_reg_read(wm8350, WM8350_DCDC4_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC4_LOW_POWER,
			val | wm8350->pmic.dcdc4_hib_mode);
		break;
	case WM8350_DCDC_6:
		val = wm8350_reg_read(wm8350, WM8350_DCDC6_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC6_LOW_POWER,
			val | wm8350->pmic.dcdc6_hib_mode);
		break;
	case WM8350_DCDC_2:
	case WM8350_DCDC_5:
	default:
		return -EINVAL;
	}

	return 0;
}