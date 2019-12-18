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
struct fsi_i2c_port {int /*<<< orphan*/  adapter; } ;
struct fsi_i2c_master {int /*<<< orphan*/  fsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_FSI_RESET_ERR ; 
 int /*<<< orphan*/  I2C_FSI_RESET_I2C ; 
 int /*<<< orphan*/  I2C_FSI_STAT ; 
 int /*<<< orphan*/  I2C_RESET_SLEEP_MAX_US ; 
 int /*<<< orphan*/  I2C_RESET_SLEEP_MIN_US ; 
 int I2C_STAT_CMD_COMP ; 
 int fsi_i2c_dev_init (struct fsi_i2c_master*) ; 
 int fsi_i2c_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int fsi_i2c_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  i2c_recover_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsi_i2c_reset_bus(struct fsi_i2c_master *i2c,
			     struct fsi_i2c_port *port)
{
	int rc;
	u32 stat, dummy = 0;

	/* force bus reset, ignore errors */
	i2c_recover_bus(&port->adapter);

	/* reset errors */
	rc = fsi_i2c_write_reg(i2c->fsi, I2C_FSI_RESET_ERR, &dummy);
	if (rc)
		return rc;

	/* wait for command complete */
	usleep_range(I2C_RESET_SLEEP_MIN_US, I2C_RESET_SLEEP_MAX_US);

	rc = fsi_i2c_read_reg(i2c->fsi, I2C_FSI_STAT, &stat);
	if (rc)
		return rc;

	if (stat & I2C_STAT_CMD_COMP)
		return 0;

	/* failed to get command complete; reset engine again */
	rc = fsi_i2c_write_reg(i2c->fsi, I2C_FSI_RESET_I2C, &dummy);
	if (rc)
		return rc;

	/* re-init engine again */
	return fsi_i2c_dev_init(i2c);
}