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
struct vctrl_voltage_range {int min_uV; int max_uV; } ;
struct TYPE_2__ {struct vctrl_voltage_range out; struct vctrl_voltage_range ctrl; } ;
struct vctrl_data {TYPE_1__ vrange; } ;
typedef  int s64 ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int vctrl_calc_output_voltage(struct vctrl_data *vctrl, int ctrl_uV)
{
	struct vctrl_voltage_range *ctrl = &vctrl->vrange.ctrl;
	struct vctrl_voltage_range *out = &vctrl->vrange.out;

	if (ctrl_uV < 0) {
		pr_err("vctrl: failed to get control voltage\n");
		return ctrl_uV;
	}

	if (ctrl_uV < ctrl->min_uV)
		return out->min_uV;

	if (ctrl_uV > ctrl->max_uV)
		return out->max_uV;

	return out->min_uV +
		DIV_ROUND_CLOSEST_ULL((s64)(ctrl_uV - ctrl->min_uV) *
				      (out->max_uV - out->min_uV),
				      ctrl->max_uV - ctrl->min_uV);
}