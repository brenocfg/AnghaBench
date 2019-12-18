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
struct gab {int /*<<< orphan*/ * channel; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int gab_prop_to_chan (int) ; 
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int read_channel(struct gab *adc_bat, enum power_supply_property psp,
		int *result)
{
	int ret;
	int chan_index;

	chan_index = gab_prop_to_chan(psp);
	ret = iio_read_channel_processed(adc_bat->channel[chan_index],
			result);
	if (ret < 0)
		pr_err("read channel error\n");
	return ret;
}