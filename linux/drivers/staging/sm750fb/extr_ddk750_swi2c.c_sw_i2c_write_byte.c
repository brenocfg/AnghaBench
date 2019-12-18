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
 int /*<<< orphan*/  sw_i2c_read_sda () ; 
 int /*<<< orphan*/  sw_i2c_scl (int) ; 
 int /*<<< orphan*/  sw_i2c_sda (int) ; 
 int /*<<< orphan*/  sw_i2c_wait () ; 

__attribute__((used)) static long sw_i2c_write_byte(unsigned char data)
{
	unsigned char value = data;
	int i;

	/* Sending the data bit by bit */
	for (i = 0; i < 8; i++) {
		/* Set SCL to low */
		sw_i2c_scl(0);

		/* Send data bit */
		if ((value & 0x80) != 0)
			sw_i2c_sda(1);
		else
			sw_i2c_sda(0);

		sw_i2c_wait();

		/* Toggle clk line to one */
		sw_i2c_scl(1);
		sw_i2c_wait();

		/* Shift byte to be sent */
		value = value << 1;
	}

	/* Set the SCL Low and SDA High (prepare to get input) */
	sw_i2c_scl(0);
	sw_i2c_sda(1);

	/* Set the SCL High for ack */
	sw_i2c_wait();
	sw_i2c_scl(1);
	sw_i2c_wait();

	/* Read SDA, until SDA==0 */
	for (i = 0; i < 0xff; i++) {
		if (!sw_i2c_read_sda())
			break;

		sw_i2c_scl(0);
		sw_i2c_wait();
		sw_i2c_scl(1);
		sw_i2c_wait();
	}

	/* Set the SCL Low and SDA High */
	sw_i2c_scl(0);
	sw_i2c_sda(1);

	if (i < 0xff)
		return 0;
	else
		return -1;
}