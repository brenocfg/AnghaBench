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
union cx25840_ir_fifo_rec {int hw_fifo_data; } ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int dummy; } ;
struct cx25840_ir_state {int /*<<< orphan*/  rx_kfifo_lock; int /*<<< orphan*/  rx_kfifo; struct i2c_client* c; } ;

/* Variables and functions */
 int CNTRL_RFE ; 
 int CNTRL_RXE ; 
 int /*<<< orphan*/  CX25840_IR_CNTRL_REG ; 
 int /*<<< orphan*/  CX25840_IR_FIFO_REG ; 
 int /*<<< orphan*/  CX25840_IR_IRQEN_REG ; 
 int CX25840_IR_RX_KFIFO_SIZE ; 
 int /*<<< orphan*/  CX25840_IR_STATS_REG ; 
 int ENODEV ; 
 int FIFO_RX_DEPTH ; 
 int FIFO_RX_NDV ; 
 int IRQEN_MSK ; 
 int IRQEN_ROE ; 
 int IRQEN_RSE ; 
 int IRQEN_RTE ; 
 int IRQEN_TSE ; 
 int STATS_RBY ; 
 int STATS_ROR ; 
 int STATS_RSR ; 
 int STATS_RTO ; 
 int STATS_TBY ; 
 int STATS_TSR ; 
 int V4L2_SUBDEV_IR_RX_END_OF_RX_DETECTED ; 
 int V4L2_SUBDEV_IR_RX_FIFO_SERVICE_REQ ; 
 int V4L2_SUBDEV_IR_RX_HW_FIFO_OVERRUN ; 
 int /*<<< orphan*/  V4L2_SUBDEV_IR_RX_NOTIFY ; 
 int V4L2_SUBDEV_IR_RX_SW_FIFO_OVERRUN ; 
 int V4L2_SUBDEV_IR_TX_FIFO_SERVICE_REQ ; 
 int /*<<< orphan*/  V4L2_SUBDEV_IR_TX_NOTIFY ; 
 int cx25840_read4 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ir_debug ; 
 int /*<<< orphan*/  irqenable_tx (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_cx23885 (struct cx25840_state*) ; 
 scalar_t__ is_cx23887 (struct cx25840_state*) ; 
 unsigned int kfifo_in_locked (int /*<<< orphan*/ *,unsigned char*,unsigned int,int /*<<< orphan*/ *) ; 
 int kfifo_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct cx25840_ir_state* to_ir_state (struct v4l2_subdev*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 
 int /*<<< orphan*/  v4l2_subdev_notify (struct v4l2_subdev*,int /*<<< orphan*/ ,int*) ; 

int cx25840_ir_irq_handler(struct v4l2_subdev *sd, u32 status, bool *handled)
{
	struct cx25840_state *state = to_state(sd);
	struct cx25840_ir_state *ir_state = to_ir_state(sd);
	struct i2c_client *c = NULL;
	unsigned long flags;

	union cx25840_ir_fifo_rec rx_data[FIFO_RX_DEPTH];
	unsigned int i, j, k;
	u32 events, v;
	int tsr, rsr, rto, ror, tse, rse, rte, roe, kror;
	u32 cntrl, irqen, stats;

	*handled = false;
	if (ir_state == NULL)
		return -ENODEV;

	c = ir_state->c;

	/* Only support the IR controller for the CX2388[57] AV Core for now */
	if (!(is_cx23885(state) || is_cx23887(state)))
		return -ENODEV;

	cntrl = cx25840_read4(c, CX25840_IR_CNTRL_REG);
	irqen = cx25840_read4(c, CX25840_IR_IRQEN_REG);
	if (is_cx23885(state) || is_cx23887(state))
		irqen ^= IRQEN_MSK;
	stats = cx25840_read4(c, CX25840_IR_STATS_REG);

	tsr = stats & STATS_TSR; /* Tx FIFO Service Request */
	rsr = stats & STATS_RSR; /* Rx FIFO Service Request */
	rto = stats & STATS_RTO; /* Rx Pulse Width Timer Time Out */
	ror = stats & STATS_ROR; /* Rx FIFO Over Run */

	tse = irqen & IRQEN_TSE; /* Tx FIFO Service Request IRQ Enable */
	rse = irqen & IRQEN_RSE; /* Rx FIFO Service Request IRQ Enable */
	rte = irqen & IRQEN_RTE; /* Rx Pulse Width Timer Time Out IRQ Enable */
	roe = irqen & IRQEN_ROE; /* Rx FIFO Over Run IRQ Enable */

	v4l2_dbg(2, ir_debug, sd, "IR IRQ Status:  %s %s %s %s %s %s\n",
		 tsr ? "tsr" : "   ", rsr ? "rsr" : "   ",
		 rto ? "rto" : "   ", ror ? "ror" : "   ",
		 stats & STATS_TBY ? "tby" : "   ",
		 stats & STATS_RBY ? "rby" : "   ");

	v4l2_dbg(2, ir_debug, sd, "IR IRQ Enables: %s %s %s %s\n",
		 tse ? "tse" : "   ", rse ? "rse" : "   ",
		 rte ? "rte" : "   ", roe ? "roe" : "   ");

	/*
	 * Transmitter interrupt service
	 */
	if (tse && tsr) {
		/*
		 * TODO:
		 * Check the watermark threshold setting
		 * Pull FIFO_TX_DEPTH or FIFO_TX_DEPTH/2 entries from tx_kfifo
		 * Push the data to the hardware FIFO.
		 * If there was nothing more to send in the tx_kfifo, disable
		 *	the TSR IRQ and notify the v4l2_device.
		 * If there was something in the tx_kfifo, check the tx_kfifo
		 *      level and notify the v4l2_device, if it is low.
		 */
		/* For now, inhibit TSR interrupt until Tx is implemented */
		irqenable_tx(sd, 0);
		events = V4L2_SUBDEV_IR_TX_FIFO_SERVICE_REQ;
		v4l2_subdev_notify(sd, V4L2_SUBDEV_IR_TX_NOTIFY, &events);
		*handled = true;
	}

	/*
	 * Receiver interrupt service
	 */
	kror = 0;
	if ((rse && rsr) || (rte && rto)) {
		/*
		 * Receive data on RSR to clear the STATS_RSR.
		 * Receive data on RTO, since we may not have yet hit the RSR
		 * watermark when we receive the RTO.
		 */
		for (i = 0, v = FIFO_RX_NDV;
		     (v & FIFO_RX_NDV) && !kror; i = 0) {
			for (j = 0;
			     (v & FIFO_RX_NDV) && j < FIFO_RX_DEPTH; j++) {
				v = cx25840_read4(c, CX25840_IR_FIFO_REG);
				rx_data[i].hw_fifo_data = v & ~FIFO_RX_NDV;
				i++;
			}
			if (i == 0)
				break;
			j = i * sizeof(union cx25840_ir_fifo_rec);
			k = kfifo_in_locked(&ir_state->rx_kfifo,
					    (unsigned char *) rx_data, j,
					    &ir_state->rx_kfifo_lock);
			if (k != j)
				kror++; /* rx_kfifo over run */
		}
		*handled = true;
	}

	events = 0;
	v = 0;
	if (kror) {
		events |= V4L2_SUBDEV_IR_RX_SW_FIFO_OVERRUN;
		v4l2_err(sd, "IR receiver software FIFO overrun\n");
	}
	if (roe && ror) {
		/*
		 * The RX FIFO Enable (CNTRL_RFE) must be toggled to clear
		 * the Rx FIFO Over Run status (STATS_ROR)
		 */
		v |= CNTRL_RFE;
		events |= V4L2_SUBDEV_IR_RX_HW_FIFO_OVERRUN;
		v4l2_err(sd, "IR receiver hardware FIFO overrun\n");
	}
	if (rte && rto) {
		/*
		 * The IR Receiver Enable (CNTRL_RXE) must be toggled to clear
		 * the Rx Pulse Width Timer Time Out (STATS_RTO)
		 */
		v |= CNTRL_RXE;
		events |= V4L2_SUBDEV_IR_RX_END_OF_RX_DETECTED;
	}
	if (v) {
		/* Clear STATS_ROR & STATS_RTO as needed by resetting hardware */
		cx25840_write4(c, CX25840_IR_CNTRL_REG, cntrl & ~v);
		cx25840_write4(c, CX25840_IR_CNTRL_REG, cntrl);
		*handled = true;
	}
	spin_lock_irqsave(&ir_state->rx_kfifo_lock, flags);
	if (kfifo_len(&ir_state->rx_kfifo) >= CX25840_IR_RX_KFIFO_SIZE / 2)
		events |= V4L2_SUBDEV_IR_RX_FIFO_SERVICE_REQ;
	spin_unlock_irqrestore(&ir_state->rx_kfifo_lock, flags);

	if (events)
		v4l2_subdev_notify(sd, V4L2_SUBDEV_IR_RX_NOTIFY, &events);
	return 0;
}