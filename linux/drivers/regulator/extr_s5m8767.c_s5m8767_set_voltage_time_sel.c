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
struct s5m8767_info {int ramp_delay; } ;
struct regulator_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int uV_step; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned int,int) ; 
 struct s5m8767_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int s5m8767_set_voltage_time_sel(struct regulator_dev *rdev,
					     unsigned int old_sel,
					     unsigned int new_sel)
{
	struct s5m8767_info *s5m8767 = rdev_get_drvdata(rdev);

	if ((old_sel < new_sel) && s5m8767->ramp_delay)
		return DIV_ROUND_UP(rdev->desc->uV_step * (new_sel - old_sel),
					s5m8767->ramp_delay * 1000);
	return 0;
}