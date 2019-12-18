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
typedef  int u8 ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int /*<<< orphan*/  redrv_addr; } ;
struct xgbe_i2c_op {int len; int* buf; int /*<<< orphan*/  target; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  redrv_data ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  XGBE_I2C_CMD_READ ; 
 int /*<<< orphan*/  XGBE_I2C_CMD_WRITE ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int xgbe_phy_i2c_xfer (struct xgbe_prv_data*,struct xgbe_i2c_op*) ; 

__attribute__((used)) static int xgbe_phy_redrv_write(struct xgbe_prv_data *pdata, unsigned int reg,
				unsigned int val)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	struct xgbe_i2c_op i2c_op;
	__be16 *redrv_val;
	u8 redrv_data[5], csum;
	unsigned int i, retry;
	int ret;

	/* High byte of register contains read/write indicator */
	redrv_data[0] = ((reg >> 8) & 0xff) << 1;
	redrv_data[1] = reg & 0xff;
	redrv_val = (__be16 *)&redrv_data[2];
	*redrv_val = cpu_to_be16(val);

	/* Calculate 1 byte checksum */
	csum = 0;
	for (i = 0; i < 4; i++) {
		csum += redrv_data[i];
		if (redrv_data[i] > csum)
			csum++;
	}
	redrv_data[4] = ~csum;

	retry = 1;
again1:
	i2c_op.cmd = XGBE_I2C_CMD_WRITE;
	i2c_op.target = phy_data->redrv_addr;
	i2c_op.len = sizeof(redrv_data);
	i2c_op.buf = redrv_data;
	ret = xgbe_phy_i2c_xfer(pdata, &i2c_op);
	if (ret) {
		if ((ret == -EAGAIN) && retry--)
			goto again1;

		return ret;
	}

	retry = 1;
again2:
	i2c_op.cmd = XGBE_I2C_CMD_READ;
	i2c_op.target = phy_data->redrv_addr;
	i2c_op.len = 1;
	i2c_op.buf = redrv_data;
	ret = xgbe_phy_i2c_xfer(pdata, &i2c_op);
	if (ret) {
		if ((ret == -EAGAIN) && retry--)
			goto again2;

		return ret;
	}

	if (redrv_data[0] != 0xff) {
		netif_dbg(pdata, drv, pdata->netdev,
			  "Redriver write checksum error\n");
		ret = -EIO;
	}

	return ret;
}