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
struct lpc2k_i2c {int msg_status; int /*<<< orphan*/  irq; int /*<<< orphan*/  wait; scalar_t__ base; int /*<<< orphan*/  msg_idx; TYPE_1__* msg; } ;
struct TYPE_2__ {int flags; scalar_t__ len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int I2C_M_NOSTART ; 
 int I2C_M_RD ; 
 scalar_t__ LPC24XX_I2CONCLR ; 
 scalar_t__ LPC24XX_I2CONSET ; 
 scalar_t__ LPC24XX_I2DAT ; 
 int /*<<< orphan*/  LPC24XX_SI ; 
 int /*<<< orphan*/  LPC24XX_STA ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lpc2k_process_msg(struct lpc2k_i2c *i2c, int msgidx)
{
	/* A new transfer is kicked off by initiating a start condition */
	if (!msgidx) {
		writel(LPC24XX_STA, i2c->base + LPC24XX_I2CONSET);
	} else {
		/*
		 * A multi-message I2C transfer continues where the
		 * previous I2C transfer left off and uses the
		 * current condition of the I2C adapter.
		 */
		if (unlikely(i2c->msg->flags & I2C_M_NOSTART)) {
			WARN_ON(i2c->msg->len == 0);

			if (!(i2c->msg->flags & I2C_M_RD)) {
				/* Start transmit of data */
				writel(i2c->msg->buf[0],
				       i2c->base + LPC24XX_I2DAT);
				i2c->msg_idx++;
			}
		} else {
			/* Start or repeated start */
			writel(LPC24XX_STA, i2c->base + LPC24XX_I2CONSET);
		}

		writel(LPC24XX_SI, i2c->base + LPC24XX_I2CONCLR);
	}

	enable_irq(i2c->irq);

	/* Wait for transfer completion */
	if (wait_event_timeout(i2c->wait, i2c->msg_status != -EBUSY,
			       msecs_to_jiffies(1000)) == 0) {
		disable_irq_nosync(i2c->irq);

		return -ETIMEDOUT;
	}

	return i2c->msg_status;
}