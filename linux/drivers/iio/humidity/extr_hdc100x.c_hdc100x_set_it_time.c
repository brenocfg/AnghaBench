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
struct hdc100x_data {int* adc_int_us; } ;
struct TYPE_2__ {int shift; int mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int** hdc100x_int_time ; 
 TYPE_1__* hdc100x_resolution_shift ; 
 int hdc100x_update_config (struct hdc100x_data*,int,int) ; 

__attribute__((used)) static int hdc100x_set_it_time(struct hdc100x_data *data, int chan, int val2)
{
	int shift = hdc100x_resolution_shift[chan].shift;
	int ret = -EINVAL;
	int i;

	for (i = 0; i < ARRAY_SIZE(hdc100x_int_time[chan]); i++) {
		if (val2 && val2 == hdc100x_int_time[chan][i]) {
			ret = hdc100x_update_config(data,
				hdc100x_resolution_shift[chan].mask << shift,
				i << shift);
			if (!ret)
				data->adc_int_us[chan] = val2;
			break;
		}
	}

	return ret;
}