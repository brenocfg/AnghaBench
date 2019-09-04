#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i2c_msg {int flags; } ;
struct i2c_adapter {int /*<<< orphan*/  timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct cdns_i2c {int err_status; TYPE_2__ adap; int /*<<< orphan*/  xfer_done; struct i2c_msg* p_msg; } ;

/* Variables and functions */
 int CDNS_I2C_CR_NEA ; 
 int /*<<< orphan*/  CDNS_I2C_CR_OFFSET ; 
 int /*<<< orphan*/  CDNS_I2C_IDR_OFFSET ; 
 int CDNS_I2C_IXR_ALL_INTR_MASK ; 
 int CDNS_I2C_IXR_ARB_LOST ; 
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 int /*<<< orphan*/  cdns_i2c_master_reset (struct i2c_adapter*) ; 
 int /*<<< orphan*/  cdns_i2c_mrecv (struct cdns_i2c*) ; 
 int /*<<< orphan*/  cdns_i2c_msend (struct cdns_i2c*) ; 
 int cdns_i2c_readreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_i2c_writereg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_i2c_process_msg(struct cdns_i2c *id, struct i2c_msg *msg,
		struct i2c_adapter *adap)
{
	unsigned long time_left;
	u32 reg;

	id->p_msg = msg;
	id->err_status = 0;
	reinit_completion(&id->xfer_done);

	/* Check for the TEN Bit mode on each msg */
	reg = cdns_i2c_readreg(CDNS_I2C_CR_OFFSET);
	if (msg->flags & I2C_M_TEN) {
		if (reg & CDNS_I2C_CR_NEA)
			cdns_i2c_writereg(reg & ~CDNS_I2C_CR_NEA,
					CDNS_I2C_CR_OFFSET);
	} else {
		if (!(reg & CDNS_I2C_CR_NEA))
			cdns_i2c_writereg(reg | CDNS_I2C_CR_NEA,
					CDNS_I2C_CR_OFFSET);
	}

	/* Check for the R/W flag on each msg */
	if (msg->flags & I2C_M_RD)
		cdns_i2c_mrecv(id);
	else
		cdns_i2c_msend(id);

	/* Wait for the signal of completion */
	time_left = wait_for_completion_timeout(&id->xfer_done, adap->timeout);
	if (time_left == 0) {
		cdns_i2c_master_reset(adap);
		dev_err(id->adap.dev.parent,
				"timeout waiting on completion\n");
		return -ETIMEDOUT;
	}

	cdns_i2c_writereg(CDNS_I2C_IXR_ALL_INTR_MASK,
			  CDNS_I2C_IDR_OFFSET);

	/* If it is bus arbitration error, try again */
	if (id->err_status & CDNS_I2C_IXR_ARB_LOST)
		return -EAGAIN;

	return 0;
}