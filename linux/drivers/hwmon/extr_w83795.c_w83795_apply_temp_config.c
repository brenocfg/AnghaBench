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
typedef  int u8 ;
struct w83795_data {int has_in; int temp_mode; int has_temp; } ;

/* Variables and functions */

__attribute__((used)) static void w83795_apply_temp_config(struct w83795_data *data, u8 config,
				     int temp_chan, int in_chan)
{
	/* config is a 2-bit value */
	switch (config) {
	case 0x2: /* Voltage monitoring */
		data->has_in |= 1 << in_chan;
		break;
	case 0x1: /* Thermal diode */
		if (temp_chan >= 4)
			break;
		data->temp_mode |= 1 << temp_chan;
		/* fall through */
	case 0x3: /* Thermistor */
		data->has_temp |= 1 << temp_chan;
		break;
	}
}