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
struct thermal_cooling_device {struct max6650_data* devdata; } ;
struct max6650_data {unsigned long cooling_dev_state; } ;

/* Variables and functions */

__attribute__((used)) static int max6650_get_cur_state(struct thermal_cooling_device *cdev,
				 unsigned long *state)
{
	struct max6650_data *data = cdev->devdata;

	*state = data->cooling_dev_state;

	return 0;
}