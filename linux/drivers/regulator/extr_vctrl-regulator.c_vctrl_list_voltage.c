#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vctrl_data {TYPE_2__* vtable; } ;
struct regulator_dev {TYPE_1__* desc; } ;
struct TYPE_4__ {int out; } ;
struct TYPE_3__ {unsigned int n_voltages; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vctrl_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int vctrl_list_voltage(struct regulator_dev *rdev,
			      unsigned int selector)
{
	struct vctrl_data *vctrl = rdev_get_drvdata(rdev);

	if (selector >= rdev->desc->n_voltages)
		return -EINVAL;

	return vctrl->vtable[selector].out;
}