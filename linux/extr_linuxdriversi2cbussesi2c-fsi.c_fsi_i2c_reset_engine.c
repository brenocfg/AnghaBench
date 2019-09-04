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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct fsi_i2c_master {int /*<<< orphan*/  fsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  I2C_FSI_MODE ; 
 int /*<<< orphan*/  I2C_FSI_PORT_BUSY ; 
 int /*<<< orphan*/  I2C_FSI_RESET_I2C ; 
 int /*<<< orphan*/  I2C_MODE_PORT ; 
 int /*<<< orphan*/  I2C_PORT_BUSY_RESET ; 
 int fsi_i2c_dev_init (struct fsi_i2c_master*) ; 
 int fsi_i2c_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fsi_i2c_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsi_i2c_reset_engine(struct fsi_i2c_master *i2c, u16 port)
{
	int rc;
	u32 mode, dummy = 0;

	/* reset engine */
	rc = fsi_i2c_write_reg(i2c->fsi, I2C_FSI_RESET_I2C, &dummy);
	if (rc)
		return rc;

	/* re-init engine */
	rc = fsi_i2c_dev_init(i2c);
	if (rc)
		return rc;

	rc = fsi_i2c_read_reg(i2c->fsi, I2C_FSI_MODE, &mode);
	if (rc)
		return rc;

	/* set port; default after reset is 0 */
	if (port) {
		mode &= ~I2C_MODE_PORT;
		mode |= FIELD_PREP(I2C_MODE_PORT, port);
		rc = fsi_i2c_write_reg(i2c->fsi, I2C_FSI_MODE, &mode);
		if (rc)
			return rc;
	}

	/* reset busy register; hw workaround */
	dummy = I2C_PORT_BUSY_RESET;
	rc = fsi_i2c_write_reg(i2c->fsi, I2C_FSI_PORT_BUSY, &dummy);
	if (rc)
		return rc;

	return 0;
}