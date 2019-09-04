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
struct hx711_data {int /*<<< orphan*/  gain_set; int /*<<< orphan*/  gpiod_dout; } ;

/* Variables and functions */
 int EIO ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int hx711_cycle (struct hx711_data*) ; 
 int hx711_get_gain_to_pulse (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hx711_read(struct hx711_data *hx711_data)
{
	int i, ret;
	int value = 0;
	int val = gpiod_get_value(hx711_data->gpiod_dout);

	/* we double check if it's really down */
	if (val)
		return -EIO;

	for (i = 0; i < 24; i++) {
		value <<= 1;
		ret = hx711_cycle(hx711_data);
		if (ret)
			value++;
	}

	value ^= 0x800000;

	for (i = 0; i < hx711_get_gain_to_pulse(hx711_data->gain_set); i++)
		hx711_cycle(hx711_data);

	return value;
}