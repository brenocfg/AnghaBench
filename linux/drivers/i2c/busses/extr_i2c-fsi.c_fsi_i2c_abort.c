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
struct fsi_i2c_port {int /*<<< orphan*/  port; struct fsi_i2c_master* master; } ;
struct fsi_i2c_master {struct fsi_device* fsi; } ;
struct fsi_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ I2C_ABORT_TIMEOUT ; 
 int /*<<< orphan*/  I2C_CMD_SLEEP_MAX_US ; 
 int /*<<< orphan*/  I2C_CMD_SLEEP_MIN_US ; 
 int I2C_CMD_WITH_STOP ; 
 int /*<<< orphan*/  I2C_FSI_CMD ; 
 int /*<<< orphan*/  I2C_FSI_STAT ; 
 int I2C_STAT_CMD_COMP ; 
 int I2C_STAT_LOST_ARB ; 
 int I2C_STAT_PARITY ; 
 int I2C_STAT_SDA_IN ; 
 int I2C_STAT_STOP_ERR ; 
 int fsi_i2c_read_reg (struct fsi_device*,int /*<<< orphan*/ ,int*) ; 
 int fsi_i2c_reset_bus (struct fsi_i2c_master*,struct fsi_i2c_port*) ; 
 int fsi_i2c_reset_engine (struct fsi_i2c_master*,int /*<<< orphan*/ ) ; 
 int fsi_i2c_write_reg (struct fsi_device*,int /*<<< orphan*/ ,int*) ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsi_i2c_abort(struct fsi_i2c_port *port, u32 status)
{
	int rc;
	unsigned long start;
	u32 cmd = I2C_CMD_WITH_STOP;
	u32 stat;
	struct fsi_i2c_master *i2c = port->master;
	struct fsi_device *fsi = i2c->fsi;

	rc = fsi_i2c_reset_engine(i2c, port->port);
	if (rc)
		return rc;

	rc = fsi_i2c_read_reg(fsi, I2C_FSI_STAT, &stat);
	if (rc)
		return rc;

	/* if sda is low, peform full bus reset */
	if (!(stat & I2C_STAT_SDA_IN)) {
		rc = fsi_i2c_reset_bus(i2c, port);
		if (rc)
			return rc;
	}

	/* skip final stop command for these errors */
	if (status & (I2C_STAT_PARITY | I2C_STAT_LOST_ARB | I2C_STAT_STOP_ERR))
		return 0;

	/* write stop command */
	rc = fsi_i2c_write_reg(fsi, I2C_FSI_CMD, &cmd);
	if (rc)
		return rc;

	/* wait until we see command complete in the master */
	start = jiffies;

	do {
		rc = fsi_i2c_read_reg(fsi, I2C_FSI_STAT, &status);
		if (rc)
			return rc;

		if (status & I2C_STAT_CMD_COMP)
			return 0;

		usleep_range(I2C_CMD_SLEEP_MIN_US, I2C_CMD_SLEEP_MAX_US);
	} while (time_after(start + I2C_ABORT_TIMEOUT, jiffies));

	return -ETIMEDOUT;
}