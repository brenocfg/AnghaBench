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
typedef  int u32 ;
struct titsc {int* config_inp; int bit_xp; int inp_xp; int bit_xn; int inp_xn; int bit_yp; int inp_yp; int bit_yn; int inp_yn; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int* config_pins ; 

__attribute__((used)) static int titsc_config_wires(struct titsc *ts_dev)
{
	u32 analog_line[4];
	u32 wire_order[4];
	int i, bit_cfg;

	for (i = 0; i < 4; i++) {
		/*
		 * Get the order in which TSC wires are attached
		 * w.r.t. each of the analog input lines on the EVM.
		 */
		analog_line[i] = (ts_dev->config_inp[i] & 0xF0) >> 4;
		wire_order[i] = ts_dev->config_inp[i] & 0x0F;
		if (WARN_ON(analog_line[i] > 7))
			return -EINVAL;
		if (WARN_ON(wire_order[i] > ARRAY_SIZE(config_pins)))
			return -EINVAL;
	}

	for (i = 0; i < 4; i++) {
		int an_line;
		int wi_order;

		an_line = analog_line[i];
		wi_order = wire_order[i];
		bit_cfg = config_pins[wi_order];
		if (bit_cfg == 0)
			return -EINVAL;
		switch (wi_order) {
		case 0:
			ts_dev->bit_xp = bit_cfg;
			ts_dev->inp_xp = an_line;
			break;

		case 1:
			ts_dev->bit_xn = bit_cfg;
			ts_dev->inp_xn = an_line;
			break;

		case 2:
			ts_dev->bit_yp = bit_cfg;
			ts_dev->inp_yp = an_line;
			break;
		case 3:
			ts_dev->bit_yn = bit_cfg;
			ts_dev->inp_yn = an_line;
			break;
		}
	}
	return 0;
}