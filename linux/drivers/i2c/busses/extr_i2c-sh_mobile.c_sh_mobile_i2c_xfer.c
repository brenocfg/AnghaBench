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
struct sh_mobile_i2c_data {int send_stop; int stop_after_dma; int sr; scalar_t__ dma_direction; int /*<<< orphan*/  dev; int /*<<< orphan*/  msg; int /*<<< orphan*/  dma_buf; int /*<<< orphan*/  wait; } ;
struct i2c_msg {int flags; } ;
struct i2c_adapter {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 scalar_t__ DMA_NONE ; 
 int ETIMEDOUT ; 
 int I2C_M_STOP ; 
 int /*<<< orphan*/  ICCR ; 
 int /*<<< orphan*/  ICCR_SCP ; 
 int ICSR_TACK ; 
 int /*<<< orphan*/  OP_START ; 
 int SW_DONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sh_mobile_i2c_data* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_op (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_put_dma_safe_msg_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iic_wr (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int poll_busy (struct sh_mobile_i2c_data*) ; 
 int poll_dte (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  sh_mobile_i2c_cleanup_dma (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  start_ch (struct sh_mobile_i2c_data*,struct i2c_msg*,int) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_i2c_xfer(struct i2c_adapter *adapter,
			      struct i2c_msg *msgs,
			      int num)
{
	struct sh_mobile_i2c_data *pd = i2c_get_adapdata(adapter);
	struct i2c_msg	*msg;
	int err = 0;
	int i;
	long timeout;

	/* Wake up device and enable clock */
	pm_runtime_get_sync(pd->dev);

	/* Process all messages */
	for (i = 0; i < num; i++) {
		bool do_start = pd->send_stop || !i;
		msg = &msgs[i];
		pd->send_stop = i == num - 1 || msg->flags & I2C_M_STOP;
		pd->stop_after_dma = false;

		start_ch(pd, msg, do_start);

		if (do_start)
			i2c_op(pd, OP_START);

		/* The interrupt handler takes care of the rest... */
		timeout = wait_event_timeout(pd->wait,
				       pd->sr & (ICSR_TACK | SW_DONE),
				       adapter->timeout);

		/* 'stop_after_dma' tells if DMA transfer was complete */
		i2c_put_dma_safe_msg_buf(pd->dma_buf, pd->msg, pd->stop_after_dma);

		if (!timeout) {
			dev_err(pd->dev, "Transfer request timed out\n");
			if (pd->dma_direction != DMA_NONE)
				sh_mobile_i2c_cleanup_dma(pd);

			err = -ETIMEDOUT;
			break;
		}

		if (pd->send_stop)
			err = poll_busy(pd);
		else
			err = poll_dte(pd);
		if (err < 0)
			break;
	}

	/* Disable channel */
	iic_wr(pd, ICCR, ICCR_SCP);

	/* Disable clock and mark device as idle */
	pm_runtime_put_sync(pd->dev);

	return err ?: num;
}