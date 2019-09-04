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
struct xgbe_prv_data {int dummy; } ;
struct xgbe_i2c_op {unsigned int target; unsigned int len; void* buf; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  XGBE_I2C_CMD_WRITE ; 
 int xgbe_phy_i2c_xfer (struct xgbe_prv_data*,struct xgbe_i2c_op*) ; 

__attribute__((used)) static int xgbe_phy_i2c_write(struct xgbe_prv_data *pdata, unsigned int target,
			      void *val, unsigned int val_len)
{
	struct xgbe_i2c_op i2c_op;
	int retry, ret;

	retry = 1;
again:
	/* Write the specfied register */
	i2c_op.cmd = XGBE_I2C_CMD_WRITE;
	i2c_op.target = target;
	i2c_op.len = val_len;
	i2c_op.buf = val;
	ret = xgbe_phy_i2c_xfer(pdata, &i2c_op);
	if ((ret == -EAGAIN) && retry--)
		goto again;

	return ret;
}