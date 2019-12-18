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
struct vctrl_data {int /*<<< orphan*/  ctrl_reg; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 struct vctrl_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int vctrl_calc_output_voltage (struct vctrl_data*,int) ; 

__attribute__((used)) static int vctrl_get_voltage(struct regulator_dev *rdev)
{
	struct vctrl_data *vctrl = rdev_get_drvdata(rdev);
	int ctrl_uV = regulator_get_voltage(vctrl->ctrl_reg);

	return vctrl_calc_output_voltage(vctrl, ctrl_uV);
}