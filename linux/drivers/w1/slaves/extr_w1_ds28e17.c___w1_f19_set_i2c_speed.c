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
typedef  size_t u8 ;
struct w1_slave {int /*<<< orphan*/  dev; int /*<<< orphan*/  master; struct w1_f19_data* family_data; } ;
struct w1_f19_data {size_t speed; } ;

/* Variables and functions */
 int EIO ; 
 size_t W1_F19_WRITE_CONFIGURATION ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int const) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (int /*<<< orphan*/ ,size_t*,int) ; 

__attribute__((used)) static int __w1_f19_set_i2c_speed(struct w1_slave *sl, u8 speed)
{
	struct w1_f19_data *data = sl->family_data;
	const int i2c_speeds[3] = { 100, 400, 900 };
	u8 w1_buf[2];

	/* Select slave. */
	if (w1_reset_select_slave(sl))
		return -EIO;

	w1_buf[0] = W1_F19_WRITE_CONFIGURATION;
	w1_buf[1] = speed;
	w1_write_block(sl->master, w1_buf, 2);

	/* Update speed in slave specific data. */
	data->speed = speed;

	dev_info(&sl->dev, "i2c speed set to %d kBaud\n", i2c_speeds[speed]);

	return 0;
}