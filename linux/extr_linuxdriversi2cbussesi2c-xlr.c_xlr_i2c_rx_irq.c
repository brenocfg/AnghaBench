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
struct xlr_i2c_private {int /*<<< orphan*/  iobase; int /*<<< orphan*/  pos; struct i2c_msg* msg; } ;
struct i2c_msg {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLR_I2C_DATAIN ; 
 int XLR_I2C_RXRDY ; 
 int /*<<< orphan*/  xlr_i2c_rdreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlr_i2c_rx_irq(struct xlr_i2c_private *priv, u32 status)
{
	struct i2c_msg *msg = priv->msg;

	if (status & XLR_I2C_RXRDY)
		msg->buf[priv->pos++] =
			xlr_i2c_rdreg(priv->iobase, XLR_I2C_DATAIN);
}