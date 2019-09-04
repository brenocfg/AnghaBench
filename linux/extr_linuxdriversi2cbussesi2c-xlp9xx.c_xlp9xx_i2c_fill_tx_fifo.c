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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct xlp9xx_i2c_dev {int /*<<< orphan*/ * msg_buf; int /*<<< orphan*/  msg_buf_remaining; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLP9XX_I2C_FIFO_SIZE ; 
 int /*<<< orphan*/  XLP9XX_I2C_MTXFIFO ; 
 size_t min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp9xx_write_i2c_reg (struct xlp9xx_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlp9xx_i2c_fill_tx_fifo(struct xlp9xx_i2c_dev *priv)
{
	u32 len, i;
	u8 *buf = priv->msg_buf;

	len = min(priv->msg_buf_remaining, XLP9XX_I2C_FIFO_SIZE);
	for (i = 0; i < len; i++)
		xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_MTXFIFO, buf[i]);
	priv->msg_buf_remaining -= len;
	priv->msg_buf += len;
}