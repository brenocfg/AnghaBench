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
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct i2c_algo_iop3xx_data {int dummy; } ;
struct i2c_adapter {struct i2c_algo_iop3xx_data* algo_data; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int iop3xx_i2c_readbytes (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iop3xx_i2c_send_target_addr (struct i2c_algo_iop3xx_data*,struct i2c_msg*) ; 
 int iop3xx_i2c_writebytes (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iop3xx_i2c_handle_msg(struct i2c_adapter *i2c_adap, struct i2c_msg* pmsg)
{
	struct i2c_algo_iop3xx_data *iop3xx_adap = i2c_adap->algo_data;
	int rc;

	rc = iop3xx_i2c_send_target_addr(iop3xx_adap, pmsg);
	if (rc < 0) {
		return rc;
	}

	if ((pmsg->flags&I2C_M_RD)) {
		return iop3xx_i2c_readbytes(i2c_adap, pmsg->buf, pmsg->len);
	} else {
		return iop3xx_i2c_writebytes(i2c_adap, pmsg->buf, pmsg->len);
	}
}