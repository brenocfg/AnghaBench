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

/* Variables and functions */
 int /*<<< orphan*/  sw_i2c_start () ; 
 int /*<<< orphan*/  sw_i2c_stop () ; 
 scalar_t__ sw_i2c_write_byte (unsigned char) ; 

long sm750_sw_i2c_write_reg(unsigned char addr,
			    unsigned char reg,
			    unsigned char data)
{
	long ret = 0;

	/* Send the Start signal */
	sw_i2c_start();

	/* Send the device address and read the data. All should return success
	 * in order for the writing processed to be successful
	 */
	if ((sw_i2c_write_byte(addr) != 0) ||
	    (sw_i2c_write_byte(reg) != 0) ||
	    (sw_i2c_write_byte(data) != 0)) {
		ret = -1;
	}

	/* Stop i2c and release the bus */
	sw_i2c_stop();

	return ret;
}