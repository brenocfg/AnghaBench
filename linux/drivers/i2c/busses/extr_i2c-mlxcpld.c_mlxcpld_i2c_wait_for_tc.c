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
typedef  int u8 ;
struct TYPE_4__ {int addr_width; int data_len; int msg_num; TYPE_1__* msg; int /*<<< orphan*/  cmd; } ;
struct mlxcpld_i2c_priv {TYPE_2__ xfer; int /*<<< orphan*/  dev; int /*<<< orphan*/  smbus_block; } ;
struct TYPE_3__ {int* buf; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  I2C_SMBUS_BLOCK_MAX ; 
 int MLXCPLD_I2C_POLL_TIME ; 
 int MLXCPLD_I2C_SMBUS_BLK_BIT ; 
 int MLXCPLD_I2C_XFER_TO ; 
#define  MLXCPLD_LPCI2C_ACK_IND 130 
 int /*<<< orphan*/  MLXCPLD_LPCI2C_DATA_REG ; 
#define  MLXCPLD_LPCI2C_NACK_IND 129 
#define  MLXCPLD_LPCI2C_NO_IND 128 
 int /*<<< orphan*/  MLXCPLD_LPCI2C_NUM_ADDR_REG ; 
 int /*<<< orphan*/  MLXCPLD_LPCI2C_NUM_DAT_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxcpld_i2c_check_status (struct mlxcpld_i2c_priv*,int*) ; 
 int /*<<< orphan*/  mlxcpld_i2c_read_comm (struct mlxcpld_i2c_priv*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mlxcpld_i2c_wait_for_tc(struct mlxcpld_i2c_priv *priv)
{
	int status, i, timeout = 0;
	u8 datalen, val;

	do {
		usleep_range(MLXCPLD_I2C_POLL_TIME / 2, MLXCPLD_I2C_POLL_TIME);
		if (!mlxcpld_i2c_check_status(priv, &status))
			break;
		timeout += MLXCPLD_I2C_POLL_TIME;
	} while (status == 0 && timeout < MLXCPLD_I2C_XFER_TO);

	switch (status) {
	case MLXCPLD_LPCI2C_NO_IND:
		return -ETIMEDOUT;

	case MLXCPLD_LPCI2C_ACK_IND:
		if (priv->xfer.cmd != I2C_M_RD)
			return (priv->xfer.addr_width + priv->xfer.data_len);

		if (priv->xfer.msg_num == 1)
			i = 0;
		else
			i = 1;

		if (!priv->xfer.msg[i].buf)
			return -EINVAL;

		/*
		 * Actual read data len will be always the same as
		 * requested len. 0xff (line pull-up) will be returned
		 * if slave has no data to return. Thus don't read
		 * MLXCPLD_LPCI2C_NUM_DAT_REG reg from CPLD.  Only in case of
		 * SMBus block read transaction data len can be different,
		 * check this case.
		 */
		mlxcpld_i2c_read_comm(priv, MLXCPLD_LPCI2C_NUM_ADDR_REG, &val,
				      1);
		if (priv->smbus_block && (val & MLXCPLD_I2C_SMBUS_BLK_BIT)) {
			mlxcpld_i2c_read_comm(priv, MLXCPLD_LPCI2C_NUM_DAT_REG,
					      &datalen, 1);
			if (unlikely(datalen > (I2C_SMBUS_BLOCK_MAX + 1))) {
				dev_err(priv->dev, "Incorrect smbus block read message len\n");
				return -E2BIG;
			}
		} else {
			datalen = priv->xfer.data_len;
		}

		mlxcpld_i2c_read_comm(priv, MLXCPLD_LPCI2C_DATA_REG,
				      priv->xfer.msg[i].buf, datalen);

		return datalen;

	case MLXCPLD_LPCI2C_NACK_IND:
		return -ENXIO;

	default:
		return -EINVAL;
	}
}