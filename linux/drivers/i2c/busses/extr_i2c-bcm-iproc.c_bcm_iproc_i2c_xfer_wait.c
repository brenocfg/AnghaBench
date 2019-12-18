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
struct i2c_msg {int dummy; } ;
struct bcm_iproc_i2c_dev {int /*<<< orphan*/  device; int /*<<< orphan*/  xfer_is_done; scalar_t__ irq; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_TIMEOUT_MSEC ; 
 int /*<<< orphan*/  IE_OFFSET ; 
 int ISR_MASK ; 
 int /*<<< orphan*/  IS_OFFSET ; 
 int /*<<< orphan*/  M_CMD_OFFSET ; 
 int /*<<< orphan*/  M_FIFO_CTRL_OFFSET ; 
 int /*<<< orphan*/  M_FIFO_RX_FLUSH_SHIFT ; 
 int /*<<< orphan*/  M_FIFO_TX_FLUSH_SHIFT ; 
 int bcm_iproc_i2c_check_status (struct bcm_iproc_i2c_dev*,struct i2c_msg*) ; 
 int /*<<< orphan*/  bcm_iproc_i2c_process_m_event (struct bcm_iproc_i2c_dev*,int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int iproc_i2c_rd_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_i2c_wr_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bcm_iproc_i2c_xfer_wait(struct bcm_iproc_i2c_dev *iproc_i2c,
				   struct i2c_msg *msg,
				   u32 cmd)
{
	unsigned long time_left = msecs_to_jiffies(I2C_TIMEOUT_MSEC);
	u32 val, status;
	int ret;

	iproc_i2c_wr_reg(iproc_i2c, M_CMD_OFFSET, cmd);

	if (iproc_i2c->irq) {
		time_left = wait_for_completion_timeout(&iproc_i2c->done,
							time_left);
		/* disable all interrupts */
		iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, 0);
		/* read it back to flush the write */
		iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
		/* make sure the interrupt handler isn't running */
		synchronize_irq(iproc_i2c->irq);

	} else { /* polling mode */
		unsigned long timeout = jiffies + time_left;

		do {
			status = iproc_i2c_rd_reg(iproc_i2c,
						  IS_OFFSET) & ISR_MASK;
			bcm_iproc_i2c_process_m_event(iproc_i2c, status);
			iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, status);

			if (time_after(jiffies, timeout)) {
				time_left = 0;
				break;
			}

			cpu_relax();
			cond_resched();
		} while (!iproc_i2c->xfer_is_done);
	}

	if (!time_left && !iproc_i2c->xfer_is_done) {
		dev_err(iproc_i2c->device, "transaction timed out\n");

		/* flush both TX/RX FIFOs */
		val = BIT(M_FIFO_RX_FLUSH_SHIFT) | BIT(M_FIFO_TX_FLUSH_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, M_FIFO_CTRL_OFFSET, val);
		return -ETIMEDOUT;
	}

	ret = bcm_iproc_i2c_check_status(iproc_i2c, msg);
	if (ret) {
		/* flush both TX/RX FIFOs */
		val = BIT(M_FIFO_RX_FLUSH_SHIFT) | BIT(M_FIFO_TX_FLUSH_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, M_FIFO_CTRL_OFFSET, val);
		return ret;
	}

	return 0;
}