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
struct hx711_data {int gain_set; int gain_chan_a; } ;

/* Variables and functions */
 int hx711_read (struct hx711_data*) ; 
 int hx711_wait_for_ready (struct hx711_data*) ; 

__attribute__((used)) static int hx711_set_gain_for_channel(struct hx711_data *hx711_data, int chan)
{
	int ret;

	if (chan == 0) {
		if (hx711_data->gain_set == 32) {
			hx711_data->gain_set = hx711_data->gain_chan_a;

			ret = hx711_read(hx711_data);
			if (ret < 0)
				return ret;

			ret = hx711_wait_for_ready(hx711_data);
			if (ret)
				return ret;
		}
	} else {
		if (hx711_data->gain_set != 32) {
			hx711_data->gain_set = 32;

			ret = hx711_read(hx711_data);
			if (ret < 0)
				return ret;

			ret = hx711_wait_for_ready(hx711_data);
			if (ret)
				return ret;
		}
	}

	return 0;
}