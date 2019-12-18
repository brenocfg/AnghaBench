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
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int REGULATOR_MODE_NORMAL ; 
#define  WM8350_DCDC_1 131 
#define  WM8350_DCDC_3 130 
#define  WM8350_DCDC_4 129 
#define  WM8350_DCDC_6 128 
 int /*<<< orphan*/  dcdc1_6_efficiency ; 
 int /*<<< orphan*/  dcdc3_4_efficiency ; 
 int get_mode (int,int /*<<< orphan*/ ) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static unsigned int wm8350_dcdc_get_optimum_mode(struct regulator_dev *rdev,
						 int input_uV, int output_uV,
						 int output_uA)
{
	int dcdc = rdev_get_id(rdev), mode;

	switch (dcdc) {
	case WM8350_DCDC_1:
	case WM8350_DCDC_6:
		mode = get_mode(output_uA, dcdc1_6_efficiency);
		break;
	case WM8350_DCDC_3:
	case WM8350_DCDC_4:
		mode = get_mode(output_uA, dcdc3_4_efficiency);
		break;
	default:
		mode = REGULATOR_MODE_NORMAL;
		break;
	}
	return mode;
}