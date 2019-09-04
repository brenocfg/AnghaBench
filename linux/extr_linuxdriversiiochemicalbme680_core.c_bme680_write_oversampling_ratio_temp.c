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
struct bme680_data {int /*<<< orphan*/  oversampling_temp; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int bme680_chip_config (struct bme680_data*) ; 
 int* bme680_oversampling_avail ; 
 int /*<<< orphan*/  ilog2 (int) ; 

__attribute__((used)) static int bme680_write_oversampling_ratio_temp(struct bme680_data *data,
						int val)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(bme680_oversampling_avail); i++) {
		if (bme680_oversampling_avail[i] == val) {
			data->oversampling_temp = ilog2(val);

			return bme680_chip_config(data);
		}
	}

	return -EINVAL;
}