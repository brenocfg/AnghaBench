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
struct TYPE_2__ {int isink_A_dcdc; int isink_B_dcdc; } ;
struct wm8350 {TYPE_1__ pmic; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8350_CS1_ENA ; 
 int WM8350_CS2_ENA ; 
 int WM8350_DCDC_1 ; 
#define  WM8350_DCDC_2 131 
#define  WM8350_DCDC_5 130 
 int /*<<< orphan*/  WM8350_DCDC_LDO_REQUESTED ; 
#define  WM8350_ISINK_A 129 
#define  WM8350_ISINK_B 128 
 int /*<<< orphan*/  WM8350_POWER_MGMT_7 ; 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8350_isink_disable(struct regulator_dev *rdev)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int isink = rdev_get_id(rdev);

	switch (isink) {
	case WM8350_ISINK_A:
		switch (wm8350->pmic.isink_A_dcdc) {
		case WM8350_DCDC_2:
		case WM8350_DCDC_5:
			wm8350_clear_bits(wm8350, WM8350_DCDC_LDO_REQUESTED,
					  1 << (wm8350->pmic.isink_A_dcdc -
						WM8350_DCDC_1));
			wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_7,
					  WM8350_CS1_ENA);
			break;
		default:
			return -EINVAL;
		}
		break;
	case WM8350_ISINK_B:
		switch (wm8350->pmic.isink_B_dcdc) {
		case WM8350_DCDC_2:
		case WM8350_DCDC_5:
			wm8350_clear_bits(wm8350, WM8350_DCDC_LDO_REQUESTED,
					  1 << (wm8350->pmic.isink_B_dcdc -
						WM8350_DCDC_1));
			wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_7,
					  WM8350_CS2_ENA);
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}