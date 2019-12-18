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
struct i2c_adapter {struct fsi_i2c_port* algo_data; } ;
struct fsi_i2c_port {struct fsi_i2c_master* master; } ;
struct fsi_i2c_master {int /*<<< orphan*/  fsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_FSI_STAT ; 
 int I2C_STAT_SCL_IN ; 
 int /*<<< orphan*/  fsi_i2c_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fsi_i2c_get_scl(struct i2c_adapter *adap)
{
	u32 stat = 0;
	struct fsi_i2c_port *port = adap->algo_data;
	struct fsi_i2c_master *i2c = port->master;

	fsi_i2c_read_reg(i2c->fsi, I2C_FSI_STAT, &stat);

	return !!(stat & I2C_STAT_SCL_IN);
}