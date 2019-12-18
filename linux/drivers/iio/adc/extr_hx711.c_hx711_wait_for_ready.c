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
struct hx711_data {int /*<<< orphan*/  gpiod_dout; } ;

/* Variables and functions */
 int EIO ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hx711_wait_for_ready(struct hx711_data *hx711_data)
{
	int i, val;

	/*
	 * in some rare cases the reset takes quite a long time
	 * especially when the channel is changed.
	 * Allow up to one second for it
	 */
	for (i = 0; i < 100; i++) {
		val = gpiod_get_value(hx711_data->gpiod_dout);
		if (!val)
			break;
		/* sleep at least 10 ms */
		msleep(10);
	}
	if (val)
		return -EIO;

	return 0;
}