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
 int /*<<< orphan*/  sw_i2c_ack () ; 
 int sw_i2c_read_sda () ; 
 int /*<<< orphan*/  sw_i2c_scl (int) ; 
 int /*<<< orphan*/  sw_i2c_sda (int) ; 
 int /*<<< orphan*/  sw_i2c_wait () ; 

__attribute__((used)) static unsigned char sw_i2c_read_byte(unsigned char ack)
{
	int i;
	unsigned char data = 0;

	for (i = 7; i >= 0; i--) {
		/* Set the SCL to Low and SDA to High (Input) */
		sw_i2c_scl(0);
		sw_i2c_sda(1);
		sw_i2c_wait();

		/* Set the SCL High */
		sw_i2c_scl(1);
		sw_i2c_wait();

		/* Read data bits from SDA */
		data |= (sw_i2c_read_sda() << i);
	}

	if (ack)
		sw_i2c_ack();

	/* Set the SCL Low and SDA High */
	sw_i2c_scl(0);
	sw_i2c_sda(1);

	return data;
}