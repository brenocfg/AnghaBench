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
struct s5p_cec_dev {int tx; int rx; int /*<<< orphan*/  msg; int /*<<< orphan*/  adap; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CEC_TX_STATUS_ERROR ; 
 int CEC_TX_STATUS_MAX_RETRIES ; 
 int CEC_TX_STATUS_NACK ; 
 int CEC_TX_STATUS_OK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  STATE_BUSY 131 
#define  STATE_DONE 130 
#define  STATE_ERROR 129 
 void* STATE_IDLE ; 
#define  STATE_NACK 128 
 int /*<<< orphan*/  cec_received_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_transmit_done (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static irqreturn_t s5p_cec_irq_handler_thread(int irq, void *priv)
{
	struct s5p_cec_dev *cec = priv;

	dev_dbg(cec->dev, "irq processing thread\n");
	switch (cec->tx) {
	case STATE_DONE:
		cec_transmit_done(cec->adap, CEC_TX_STATUS_OK, 0, 0, 0, 0);
		cec->tx = STATE_IDLE;
		break;
	case STATE_NACK:
		cec_transmit_done(cec->adap,
			CEC_TX_STATUS_MAX_RETRIES | CEC_TX_STATUS_NACK,
			0, 1, 0, 0);
		cec->tx = STATE_IDLE;
		break;
	case STATE_ERROR:
		cec_transmit_done(cec->adap,
			CEC_TX_STATUS_MAX_RETRIES | CEC_TX_STATUS_ERROR,
			0, 0, 0, 1);
		cec->tx = STATE_IDLE;
		break;
	case STATE_BUSY:
		dev_err(cec->dev, "state set to busy, this should not occur here\n");
		break;
	default:
		break;
	}

	switch (cec->rx) {
	case STATE_DONE:
		cec_received_msg(cec->adap, &cec->msg);
		cec->rx = STATE_IDLE;
		break;
	default:
		break;
	}

	return IRQ_HANDLED;
}