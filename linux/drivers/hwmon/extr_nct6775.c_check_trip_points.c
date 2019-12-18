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
struct nct6775_data {int auto_pwm_num; scalar_t__** auto_temp; scalar_t__** auto_pwm; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int check_trip_points(struct nct6775_data *data, int nr)
{
	int i;

	for (i = 0; i < data->auto_pwm_num - 1; i++) {
		if (data->auto_temp[nr][i] > data->auto_temp[nr][i + 1])
			return -EINVAL;
	}
	for (i = 0; i < data->auto_pwm_num - 1; i++) {
		if (data->auto_pwm[nr][i] > data->auto_pwm[nr][i + 1])
			return -EINVAL;
	}
	/* validate critical temperature and pwm if enabled (pwm > 0) */
	if (data->auto_pwm[nr][data->auto_pwm_num]) {
		if (data->auto_temp[nr][data->auto_pwm_num - 1] >
				data->auto_temp[nr][data->auto_pwm_num] ||
		    data->auto_pwm[nr][data->auto_pwm_num - 1] >
				data->auto_pwm[nr][data->auto_pwm_num])
			return -EINVAL;
	}
	return 0;
}