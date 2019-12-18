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
struct fsi_i2c_port {scalar_t__ port; TYPE_1__* master; } ;
struct fsi_device {int dummy; } ;
struct TYPE_2__ {struct fsi_device* fsi; } ;

/* Variables and functions */
 scalar_t__ FIELD_GET (int,int) ; 
 int FIELD_PREP (int,scalar_t__) ; 
 int /*<<< orphan*/  I2C_FSI_MODE ; 
 int /*<<< orphan*/  I2C_FSI_RESET_ERR ; 
 int I2C_MODE_PORT ; 
 int fsi_i2c_read_reg (struct fsi_device*,int /*<<< orphan*/ ,int*) ; 
 int fsi_i2c_write_reg (struct fsi_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fsi_i2c_set_port(struct fsi_i2c_port *port)
{
	int rc;
	struct fsi_device *fsi = port->master->fsi;
	u32 mode, dummy = 0;

	rc = fsi_i2c_read_reg(fsi, I2C_FSI_MODE, &mode);
	if (rc)
		return rc;

	if (FIELD_GET(I2C_MODE_PORT, mode) == port->port)
		return 0;

	mode = (mode & ~I2C_MODE_PORT) | FIELD_PREP(I2C_MODE_PORT, port->port);
	rc = fsi_i2c_write_reg(fsi, I2C_FSI_MODE, &mode);
	if (rc)
		return rc;

	/* reset engine when port is changed */
	return fsi_i2c_write_reg(fsi, I2C_FSI_RESET_ERR, &dummy);
}