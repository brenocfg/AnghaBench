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
struct it87_data {scalar_t__** auto_temp; scalar_t__** auto_pwm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct it87_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ has_newer_autopwm (struct it87_data const*) ; 
 scalar_t__ has_old_autopwm (struct it87_data const*) ; 

__attribute__((used)) static int check_trip_points(struct device *dev, int nr)
{
	const struct it87_data *data = dev_get_drvdata(dev);
	int i, err = 0;

	if (has_old_autopwm(data)) {
		for (i = 0; i < 3; i++) {
			if (data->auto_temp[nr][i] > data->auto_temp[nr][i + 1])
				err = -EINVAL;
		}
		for (i = 0; i < 2; i++) {
			if (data->auto_pwm[nr][i] > data->auto_pwm[nr][i + 1])
				err = -EINVAL;
		}
	} else if (has_newer_autopwm(data)) {
		for (i = 1; i < 3; i++) {
			if (data->auto_temp[nr][i] > data->auto_temp[nr][i + 1])
				err = -EINVAL;
		}
	}

	if (err) {
		dev_err(dev,
			"Inconsistent trip points, not switching to automatic mode\n");
		dev_err(dev, "Adjust the trip points and try again\n");
	}
	return err;
}