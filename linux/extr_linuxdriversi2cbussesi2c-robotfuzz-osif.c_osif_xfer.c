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
struct osif_priv {scalar_t__ status; } ;
struct i2c_msg {int flags; scalar_t__* buf; int len; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; struct osif_priv* algo_data; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  OSIFI2C_READ ; 
 int /*<<< orphan*/  OSIFI2C_STATUS ; 
 int /*<<< orphan*/  OSIFI2C_STOP ; 
 int /*<<< orphan*/  OSIFI2C_WRITE ; 
 scalar_t__ STATUS_ADDRESS_ACK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int osif_usb_read (struct i2c_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int osif_usb_write (struct i2c_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int osif_xfer(struct i2c_adapter *adapter, struct i2c_msg *msgs,
			 int num)
{
	struct osif_priv *priv = adapter->algo_data;
	struct i2c_msg *pmsg;
	int ret;
	int i;

	for (i = 0; i < num; i++) {
		pmsg = &msgs[i];

		if (pmsg->flags & I2C_M_RD) {
			ret = osif_usb_read(adapter, OSIFI2C_READ,
					    pmsg->flags, pmsg->addr,
					    pmsg->buf, pmsg->len);
			if (ret != pmsg->len) {
				dev_err(&adapter->dev, "failure reading data\n");
				return -EREMOTEIO;
			}
		} else {
			ret = osif_usb_write(adapter, OSIFI2C_WRITE,
					     pmsg->flags, pmsg->addr,
					     pmsg->buf, pmsg->len);
			if (ret != pmsg->len) {
				dev_err(&adapter->dev, "failure writing data\n");
				return -EREMOTEIO;
			}
		}

		ret = osif_usb_read(adapter, OSIFI2C_STOP, 0, 0, NULL, 0);
		if (ret) {
			dev_err(&adapter->dev, "failure sending STOP\n");
			return -EREMOTEIO;
		}

		/* read status */
		ret = osif_usb_read(adapter, OSIFI2C_STATUS, 0, 0,
				    &priv->status, 1);
		if (ret != 1) {
			dev_err(&adapter->dev, "failure reading status\n");
			return -EREMOTEIO;
		}

		if (priv->status != STATUS_ADDRESS_ACK) {
			dev_dbg(&adapter->dev, "status = %d\n", priv->status);
			return -EREMOTEIO;
		}
	}

	return i;
}