#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int len; int /*<<< orphan*/  msg; } ;
struct tda9950_priv {TYPE_1__* client; TYPE_3__ rx_msg; int /*<<< orphan*/  adap; int /*<<< orphan*/  open; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CCONR_RETRY_MASK ; 
#define  CDR1_CNF 132 
#define  CDR1_IND 131 
#define  CDR2_CNF_ARB_ERROR 130 
#define  CDR2_CNF_NACK_ADDR 129 
#define  CDR2_CNF_SUCCESS 128 
 int CEC_MAX_MSG_SIZE ; 
 unsigned int CEC_TX_STATUS_ARB_LOST ; 
 unsigned int CEC_TX_STATUS_ERROR ; 
 unsigned int CEC_TX_STATUS_MAX_RETRIES ; 
 unsigned int CEC_TX_STATUS_NACK ; 
 unsigned int CEC_TX_STATUS_OK ; 
 int CSR_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  REG_CCONR ; 
 int /*<<< orphan*/  REG_CDR0 ; 
 int /*<<< orphan*/  REG_CSR ; 
 int /*<<< orphan*/  cec_received_msg (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  cec_transmit_done (int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int tda9950_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda9950_read_range (TYPE_1__*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static irqreturn_t tda9950_irq(int irq, void *data)
{
	struct tda9950_priv *priv = data;
	unsigned int tx_status;
	u8 csr, cconr, buf[19];
	u8 arb_lost_cnt, nack_cnt, err_cnt;

	if (!priv->open)
		return IRQ_NONE;

	csr = tda9950_read(priv->client, REG_CSR);
	if (!(csr & CSR_INT))
		return IRQ_NONE;

	cconr = tda9950_read(priv->client, REG_CCONR) & CCONR_RETRY_MASK;

	tda9950_read_range(priv->client, REG_CDR0, buf, sizeof(buf));

	/*
	 * This should never happen: the data sheet says that there will
	 * always be a valid message if the interrupt line is asserted.
	 */
	if (buf[0] == 0) {
		dev_warn(&priv->client->dev, "interrupt pending, but no message?\n");
		return IRQ_NONE;
	}

	switch (buf[1]) {
	case CDR1_CNF: /* transmit result */
		arb_lost_cnt = nack_cnt = err_cnt = 0;
		switch (buf[2]) {
		case CDR2_CNF_SUCCESS:
			tx_status = CEC_TX_STATUS_OK;
			break;

		case CDR2_CNF_ARB_ERROR:
			tx_status = CEC_TX_STATUS_ARB_LOST;
			arb_lost_cnt = cconr;
			break;

		case CDR2_CNF_NACK_ADDR:
			tx_status = CEC_TX_STATUS_NACK;
			nack_cnt = cconr;
			break;

		default: /* some other error, refer to TDA9950 docs */
			dev_err(&priv->client->dev, "CNF reply error 0x%02x\n",
				buf[2]);
			tx_status = CEC_TX_STATUS_ERROR;
			err_cnt = cconr;
			break;
		}
		/* TDA9950 executes all retries for us */
		if (tx_status != CEC_TX_STATUS_OK)
			tx_status |= CEC_TX_STATUS_MAX_RETRIES;
		cec_transmit_done(priv->adap, tx_status, arb_lost_cnt,
				  nack_cnt, 0, err_cnt);
		break;

	case CDR1_IND:
		priv->rx_msg.len = buf[0] - 2;
		if (priv->rx_msg.len > CEC_MAX_MSG_SIZE)
			priv->rx_msg.len = CEC_MAX_MSG_SIZE;

		memcpy(priv->rx_msg.msg, buf + 2, priv->rx_msg.len);
		cec_received_msg(priv->adap, &priv->rx_msg);
		break;

	default: /* unknown */
		dev_err(&priv->client->dev, "unknown service id 0x%02x\n",
			buf[1]);
		break;
	}

	return IRQ_HANDLED;
}