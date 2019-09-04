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
struct hx711_data {int /*<<< orphan*/  gpiod_pd_sck; int /*<<< orphan*/  gpiod_dout; } ;

/* Variables and functions */
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int hx711_read (struct hx711_data*) ; 
 int hx711_wait_for_ready (struct hx711_data*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hx711_reset(struct hx711_data *hx711_data)
{
	int ret;
	int val = gpiod_get_value(hx711_data->gpiod_dout);

	if (val) {
		/*
		 * an examination with the oszilloscope indicated
		 * that the first value read after the reset is not stable
		 * if we reset too short;
		 * the shorter the reset cycle
		 * the less reliable the first value after reset is;
		 * there were no problems encountered with a value
		 * of 10 ms or higher
		 */
		gpiod_set_value(hx711_data->gpiod_pd_sck, 1);
		msleep(10);
		gpiod_set_value(hx711_data->gpiod_pd_sck, 0);

		ret = hx711_wait_for_ready(hx711_data);
		if (ret)
			return ret;
		/*
		 * after a reset the gain is 128 so we do a dummy read
		 * to set the gain for the next read
		 */
		ret = hx711_read(hx711_data);
		if (ret < 0)
			return ret;

		/*
		 * after a dummy read we need to wait vor readiness
		 * for not mixing gain pulses with the clock
		 */
		val = hx711_wait_for_ready(hx711_data);
	}

	return val;
}