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
struct bmp280_data {TYPE_1__* chip_info; int /*<<< orphan*/  oversampling_temp; } ;
struct TYPE_2__ {int* oversampling_temp_avail; int num_oversampling_temp_avail; int (* chip_config ) (struct bmp280_data*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int stub1 (struct bmp280_data*) ; 

__attribute__((used)) static int bmp280_write_oversampling_ratio_temp(struct bmp280_data *data,
					       int val)
{
	int i;
	const int *avail = data->chip_info->oversampling_temp_avail;
	const int n = data->chip_info->num_oversampling_temp_avail;

	for (i = 0; i < n; i++) {
		if (avail[i] == val) {
			data->oversampling_temp = ilog2(val);

			return data->chip_info->chip_config(data);
		}
	}
	return -EINVAL;
}