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
struct xlp9xx_i2c_dev {int msg_buf_remaining; scalar_t__ len_recv; } ;

/* Variables and functions */
 int XLP9XX_I2C_FIFO_SIZE ; 
 int /*<<< orphan*/  XLP9XX_I2C_MFIFOCTRL ; 
 int XLP9XX_I2C_MFIFOCTRL_HITH_SHIFT ; 
 int /*<<< orphan*/  xlp9xx_write_i2c_reg (struct xlp9xx_i2c_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlp9xx_i2c_update_rx_fifo_thres(struct xlp9xx_i2c_dev *priv)
{
	u32 thres;

	if (priv->len_recv)
		/* interrupt after the first read to examine
		 * the length byte before proceeding further
		 */
		thres = 1;
	else if (priv->msg_buf_remaining > XLP9XX_I2C_FIFO_SIZE)
		thres = XLP9XX_I2C_FIFO_SIZE;
	else
		thres = priv->msg_buf_remaining;

	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_MFIFOCTRL,
			     thres << XLP9XX_I2C_MFIFOCTRL_HITH_SHIFT);
}