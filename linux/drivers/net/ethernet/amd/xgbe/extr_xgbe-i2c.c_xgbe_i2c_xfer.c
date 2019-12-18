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
struct xgbe_i2c_op_state {int ret; int tx_abort_source; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  rx_len; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  tx_len; struct xgbe_i2c_op* op; } ;
struct TYPE_2__ {struct xgbe_i2c_op_state op_state; } ;
struct xgbe_prv_data {int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  netdev; int /*<<< orphan*/  i2c_complete; TYPE_1__ i2c; } ;
struct xgbe_i2c_op {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOTCONN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int IC_TX_ABRT_7B_ADDR_NOACK ; 
 int IC_TX_ABRT_ARB_LOST ; 
 int /*<<< orphan*/  memset (struct xgbe_i2c_op_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_i2c_clear_all_interrupts (struct xgbe_prv_data*) ; 
 int xgbe_i2c_disable (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_disable_interrupts (struct xgbe_prv_data*) ; 
 int xgbe_i2c_enable (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_enable_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_set_target (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_i2c_xfer(struct xgbe_prv_data *pdata, struct xgbe_i2c_op *op)
{
	struct xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	int ret;

	mutex_lock(&pdata->i2c_mutex);

	reinit_completion(&pdata->i2c_complete);

	ret = xgbe_i2c_disable(pdata);
	if (ret) {
		netdev_err(pdata->netdev, "failed to disable i2c master\n");
		goto unlock;
	}

	xgbe_i2c_set_target(pdata, op->target);

	memset(state, 0, sizeof(*state));
	state->op = op;
	state->tx_len = op->len;
	state->tx_buf = op->buf;
	state->rx_len = op->len;
	state->rx_buf = op->buf;

	xgbe_i2c_clear_all_interrupts(pdata);
	ret = xgbe_i2c_enable(pdata);
	if (ret) {
		netdev_err(pdata->netdev, "failed to enable i2c master\n");
		goto unlock;
	}

	/* Enabling the interrupts will cause the TX FIFO empty interrupt to
	 * fire and begin to process the command via the ISR.
	 */
	xgbe_i2c_enable_interrupts(pdata);

	if (!wait_for_completion_timeout(&pdata->i2c_complete, HZ)) {
		netdev_err(pdata->netdev, "i2c operation timed out\n");
		ret = -ETIMEDOUT;
		goto disable;
	}

	ret = state->ret;
	if (ret) {
		if (state->tx_abort_source & IC_TX_ABRT_7B_ADDR_NOACK)
			ret = -ENOTCONN;
		else if (state->tx_abort_source & IC_TX_ABRT_ARB_LOST)
			ret = -EAGAIN;
	}

disable:
	xgbe_i2c_disable_interrupts(pdata);
	xgbe_i2c_disable(pdata);

unlock:
	mutex_unlock(&pdata->i2c_mutex);

	return ret;
}