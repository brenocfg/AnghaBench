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
typedef  int u16 ;
struct w1_slave {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC16_INIT ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 
 int W1_F19_READ_DATA_WITH_STOP ; 
 int crc16 (int /*<<< orphan*/ ,int*,int) ; 
 int w1_f19_error (struct w1_slave*,int*) ; 
 scalar_t__ w1_f19_i2c_busy_wait (struct w1_slave*,size_t) ; 
 int w1_read_8 (int /*<<< orphan*/ ) ; 
 int w1_read_block (int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  w1_write_block (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int w1_f19_i2c_read(struct w1_slave *sl, u16 i2c_address,
	u8 *buffer, size_t count)
{
	u16 crc;
	int error;
	u8 w1_buf[5];

	/* Check input. */
	if (count == 0)
		return -EOPNOTSUPP;

	/* Send command to DS28E17. */
	w1_buf[0] = W1_F19_READ_DATA_WITH_STOP;
	w1_buf[1] = i2c_address << 1 | 0x01;
	w1_buf[2] = count;
	crc = crc16(CRC16_INIT, w1_buf, 3);
	w1_buf[3] = ~(crc & 0xFF);
	w1_buf[4] = ~((crc >> 8) & 0xFF);
	w1_write_block(sl->master, w1_buf, 5);

	/* Wait until busy flag clears (or timeout). */
	if (w1_f19_i2c_busy_wait(sl, count + 1) < 0)
		return -ETIMEDOUT;

	/* Read status from DS28E17. */
	w1_buf[0] = w1_read_8(sl->master);
	w1_buf[1] = 0;

	/* Check error conditions. */
	error = w1_f19_error(sl, w1_buf);
	if (error < 0)
		return error;

	/* Read received I2C data from DS28E17. */
	return w1_read_block(sl->master, buffer, count);
}