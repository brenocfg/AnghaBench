#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hix5hd2_i2c_priv {int err; scalar_t__ state; scalar_t__ msg_len; scalar_t__ msg_idx; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_complete; TYPE_1__* msg; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; scalar_t__ len; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENXIO ; 
 scalar_t__ HIX5I2C_STAT_RW_ERR ; 
 scalar_t__ HIX5I2C_STAT_RW_SUCCESS ; 
 int I2C_ACK_INTR ; 
 int I2C_ARBITRATE_INTR ; 
 int I2C_M_RD ; 
 int I2C_OVER_INTR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int hix5hd2_i2c_clr_pend_irq (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  hix5hd2_i2c_disable_irq (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  hix5hd2_read_handle (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  hix5hd2_rw_over (struct hix5hd2_i2c_priv*) ; 
 int hix5hd2_rw_preprocess (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  hix5hd2_write_handle (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t hix5hd2_i2c_irq(int irqno, void *dev_id)
{
	struct hix5hd2_i2c_priv *priv = dev_id;
	u32 int_status;
	int ret;

	spin_lock(&priv->lock);

	int_status = hix5hd2_i2c_clr_pend_irq(priv);

	/* handle error */
	if (int_status & I2C_ARBITRATE_INTR) {
		/* bus error */
		dev_dbg(priv->dev, "ARB bus loss\n");
		priv->err = -EAGAIN;
		priv->state = HIX5I2C_STAT_RW_ERR;
		goto stop;
	} else if (int_status & I2C_ACK_INTR) {
		/* ack error */
		dev_dbg(priv->dev, "No ACK from device\n");
		priv->err = -ENXIO;
		priv->state = HIX5I2C_STAT_RW_ERR;
		goto stop;
	}

	if (int_status & I2C_OVER_INTR) {
		if (priv->msg_len > 0) {
			ret = hix5hd2_rw_preprocess(priv);
			if (ret) {
				priv->err = ret;
				priv->state = HIX5I2C_STAT_RW_ERR;
				goto stop;
			}
			if (priv->msg->flags & I2C_M_RD)
				hix5hd2_read_handle(priv);
			else
				hix5hd2_write_handle(priv);
		} else {
			hix5hd2_rw_over(priv);
		}
	}

stop:
	if ((priv->state == HIX5I2C_STAT_RW_SUCCESS &&
	     priv->msg->len == priv->msg_idx) ||
	    (priv->state == HIX5I2C_STAT_RW_ERR)) {
		hix5hd2_i2c_disable_irq(priv);
		hix5hd2_i2c_clr_pend_irq(priv);
		complete(&priv->msg_complete);
	}

	spin_unlock(&priv->lock);

	return IRQ_HANDLED;
}