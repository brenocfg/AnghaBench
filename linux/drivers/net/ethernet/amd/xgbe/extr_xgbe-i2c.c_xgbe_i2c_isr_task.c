#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xgbe_i2c_op_state {int /*<<< orphan*/  ret; TYPE_2__* op; int /*<<< orphan*/  tx_abort_source; } ;
struct TYPE_4__ {struct xgbe_i2c_op_state op_state; } ;
struct xgbe_prv_data {TYPE_3__* vdata; int /*<<< orphan*/  i2c_complete; int /*<<< orphan*/  netdev; TYPE_1__ i2c; } ;
struct TYPE_6__ {scalar_t__ irq_reissue_support; } ;
struct TYPE_5__ {int /*<<< orphan*/  target; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IC_RAW_INTR_STAT ; 
 int /*<<< orphan*/  STOP_DET ; 
 unsigned int XGBE_INTR_TX_ABRT ; 
 scalar_t__ XI2C_GET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int XI2C_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XP_INT_REISSUE_EN ; 
 int /*<<< orphan*/  XP_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  xgbe_i2c_clear_isr_interrupts (struct xgbe_prv_data*,unsigned int) ; 
 int /*<<< orphan*/  xgbe_i2c_disable_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_read (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_write (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_i2c_isr_task(unsigned long data)
{
	struct xgbe_prv_data *pdata = (struct xgbe_prv_data *)data;
	struct xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	unsigned int isr;

	isr = XI2C_IOREAD(pdata, IC_RAW_INTR_STAT);
	if (!isr)
		goto reissue_check;

	netif_dbg(pdata, intr, pdata->netdev,
		  "I2C interrupt received: status=%#010x\n", isr);

	xgbe_i2c_clear_isr_interrupts(pdata, isr);

	if (isr & XGBE_INTR_TX_ABRT) {
		netif_dbg(pdata, link, pdata->netdev,
			  "I2C TX_ABRT received (%#010x) for target %#04x\n",
			  state->tx_abort_source, state->op->target);

		xgbe_i2c_disable_interrupts(pdata);

		state->ret = -EIO;
		goto out;
	}

	/* Check for data in the Rx fifo */
	xgbe_i2c_read(pdata);

	/* Fill up the Tx fifo next */
	xgbe_i2c_write(pdata);

out:
	/* Complete on an error or STOP condition */
	if (state->ret || XI2C_GET_BITS(isr, IC_RAW_INTR_STAT, STOP_DET))
		complete(&pdata->i2c_complete);

reissue_check:
	/* Reissue interrupt if status is not clear */
	if (pdata->vdata->irq_reissue_support)
		XP_IOWRITE(pdata, XP_INT_REISSUE_EN, 1 << 2);
}