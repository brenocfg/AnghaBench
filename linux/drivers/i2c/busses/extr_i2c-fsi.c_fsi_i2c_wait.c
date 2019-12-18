#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i2c_msg {int len; } ;
struct fsi_i2c_port {TYPE_1__* master; } ;
struct TYPE_2__ {int /*<<< orphan*/  fsi; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_CMD_SLEEP_MAX_US ; 
 int /*<<< orphan*/  I2C_CMD_SLEEP_MIN_US ; 
 int /*<<< orphan*/  I2C_FSI_STAT ; 
 int I2C_STAT_ANY_RESP ; 
 int fsi_i2c_handle_status (struct fsi_i2c_port*,struct i2c_msg*,int) ; 
 int fsi_i2c_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsi_i2c_wait(struct fsi_i2c_port *port, struct i2c_msg *msg,
			unsigned long timeout)
{
	u32 status = 0;
	int rc;
	unsigned long start = jiffies;

	do {
		rc = fsi_i2c_read_reg(port->master->fsi, I2C_FSI_STAT,
				      &status);
		if (rc)
			return rc;

		if (status & I2C_STAT_ANY_RESP) {
			rc = fsi_i2c_handle_status(port, msg, status);
			if (rc < 0)
				return rc;

			/* cmd complete and all data xfrd */
			if (rc == msg->len)
				return 0;

			/* need to xfr more data, but maybe don't need wait */
			continue;
		}

		usleep_range(I2C_CMD_SLEEP_MIN_US, I2C_CMD_SLEEP_MAX_US);
	} while (time_after(start + timeout, jiffies));

	return -ETIMEDOUT;
}