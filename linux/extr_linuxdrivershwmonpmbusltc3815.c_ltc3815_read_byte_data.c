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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
#define  PMBUS_VOUT_MODE 128 

__attribute__((used)) static int ltc3815_read_byte_data(struct i2c_client *client, int page, int reg)
{
	int ret;

	switch (reg) {
	case PMBUS_VOUT_MODE:
		/*
		 * The chip returns 0x3e, suggesting VID mode with manufacturer
		 * specific VID codes. Since the output voltage is reported
		 * with a LSB of 0.5mV, override and report direct mode with
		 * appropriate coefficients.
		 */
		ret = 0x40;
		break;
	default:
		ret = -ENODATA;
		break;
	}
	return ret;
}